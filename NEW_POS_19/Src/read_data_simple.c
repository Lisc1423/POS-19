/*
 ******************************************************************************
 * @file    read_data_simple.c
 * @author  Sensor Solutions Software Team
 * @brief   This file show the simplest way to get data from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "asm330lhh_reg.h"
#include <string.h>

#define MKI109V2

#ifdef MKI109V2
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "cmd.h"
#endif

/* Private macro -------------------------------------------------------------*/
#ifdef MKI109V2
#define CS_SPI2_GPIO_Port   GPIOC
#define CS_SPI2_Pin         GPIO_PIN_13

#endif

/* Private variables ---------------------------------------------------------*/

static axis3bit16_t data_raw_acceleration;
static axis3bit16_t data_raw_angular_rate;
static float acceleration_mg[3];
static float angular_rate_mdps[3];
static float temperature_degC;
static uint8_t whoamI, rst;


/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   Replace the functions "platform_write" and "platform_read" with your
 *   platform specific read and write function.
 *   This example use an STM32 evaluation board and CubeMX tool.
 *   In this case the "*handle" variable is useful in order to select the
 *   correct interface but the usage of "*handle" is not mandatory.
 */

static int32_t platform_write(void *handle, uint8_t Reg, uint8_t *Bufp,
                              uint16_t len)
{
  
#ifdef MKI109V2
   if (handle == &hspi2)
  {
    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, &Reg, 1, 1000);
    HAL_SPI_Transmit(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(CS_SPI2_GPIO_Port, CS_SPI2_Pin, GPIO_PIN_SET);
  }
#endif
  return 0;
}

static int32_t platform_read(void *handle, uint8_t Reg, uint8_t *Bufp,
                             uint16_t len)
{

#ifdef MKI109V2
   if (handle == &hspi2)
  {
//    uint16_t reg = (uint16_t)Reg |0x80;
//    reg=reg<<8;
    Reg |=0x80;
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_SPI_Transmit(handle, (uint8_t*)&Reg, 1, 1000);
    HAL_SPI_Receive(handle, Bufp, len, 1000);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  }
  
#endif
  return 0;
}

/*
 *  Function to print messages.
 */


/*
 * Function to wait for a timeout.
 */
static void platform_delay(uint32_t timeout)
{
	/*
	 * Force compiler to not optimize this code.
	 */
	volatile uint32_t i;

	for(i = 0; i < timeout; i++);
}

/*
 * Platform specific initialization.
 */

/*
 * Main Example
 *
 * Set Acc/Gyro ODR to 12.5 Hz
 * Set full scale to 2g (XL) 2000dps (Gyro)
 * Select LPF2 bandwidth to ODR/100
 * Enable digital data path to LPF2
 */

void example_main_asm330lhh(void)
{
  asm330lhh_ctx_t dev_ctx;

  /*
   *  Initialize mems driver interface.
   */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &hspi2;

  /*
   * Init test platform.
   */

  asm330lhh_reg_t hh;
    asm330lhh_status_reg_get(&dev_ctx, &hh.status_reg);
  /*
   *  Check device ID.
   */
  asm330lhh_device_id_get(&dev_ctx, &whoamI);
  if (whoamI != ASM330LHH_ID)
    while(1)
    {
      asm330lhh_device_id_get(&dev_ctx, &whoamI);
    };

  /*
   *  Restore default configuration.
   */
  asm330lhh_reset_set(&dev_ctx, PROPERTY_ENABLE);
  do {
    asm330lhh_reset_get(&dev_ctx, &rst);
  } while (rst);


  /*
   *  Enable Block Data Update.
   */
  asm330lhh_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Set Output Data Rate.
   */
  asm330lhh_xl_data_rate_set(&dev_ctx, ASM330LHH_XL_ODR_12Hz5);
  asm330lhh_gy_data_rate_set(&dev_ctx, ASM330LHH_GY_ODR_12Hz5);

  /*
   * Set full scale.
   */
  asm330lhh_xl_full_scale_set(&dev_ctx, ASM330LHH_2g);
  asm330lhh_gy_full_scale_set(&dev_ctx, ASM330LHH_2000dps);

  
  /*
   * Configure filtering chain(No aux interface).
   */
  /*
   * Accelerometer - LPF1 + LPF2 path.
   */
  asm330lhh_xl_hp_path_on_out_set(&dev_ctx, ASM330LHH_LP_ODR_DIV_100);
  asm330lhh_xl_filter_lp2_set(&dev_ctx, PROPERTY_ENABLE);

  /*
   * Read samples in polling mode (no int).
   */
  while(1)
  {
    /*
     * Read output only if new value is available.
     */
    asm330lhh_reg_t reg;
    asm330lhh_status_reg_get(&dev_ctx, &reg.status_reg);

    if (reg.status_reg.xlda)
    {
      /*
       * Read acceleration field data.
       */
      memset(data_raw_acceleration.u8bit, 0x00, 3 * sizeof(int16_t));
      asm330lhh_acceleration_raw_get(&dev_ctx, data_raw_acceleration.u8bit);
      acceleration_mg[0] =
    		  asm330lhh_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
      acceleration_mg[1] =
    		  asm330lhh_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
      acceleration_mg[2] =
    		  asm330lhh_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);

      uprintf("%f\r\n",acceleration_mg[0]);
    }
    if (reg.status_reg.gda)
    {
      /*
       * Read angular rate field data.
       */
      memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
      asm330lhh_angular_rate_raw_get(&dev_ctx, data_raw_angular_rate.u8bit);
      angular_rate_mdps[0] =
    		  asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
      angular_rate_mdps[1] =
    		  asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
      angular_rate_mdps[2] =
    		  asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);

      uprintf("%f\r\n",angular_rate_mdps[0]);
      uprintf("%f\r\n",angular_rate_mdps[1]);
      uprintf("%f\r\n",angular_rate_mdps[2]);
    }
    
  }
}

