
#include "stm32f4xx_hal.h"
#include "Asm330lhh.h"
#include "string.h"
#include "spi.h"

/*
   * Set Output Data Rate
   */
//  asm330lhh_xl_data_rate_set(&dev_ctx, ASM330LHH_XL_ODR_12Hz5);
//  asm330lhh_gy_data_rate_set(&dev_ctx, ASM330LHH_GY_ODR_12Hz5);
  





 axis3bit16_t data_raw_angular_rate;
 float angular_rate_mdps[3];


void get_anglespeed()
{
  memset(data_raw_angular_rate.u8bit, 0x00, 3 * sizeof(int16_t));
  asm330lhh_angular_rate_raw_get(&hspi2, data_raw_angular_rate.u8bit);
  angular_rate_mdps[0] =
    asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
  angular_rate_mdps[1] =
    asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
  angular_rate_mdps[2] =
    asm330lhh_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);
}
      


float asm330lhh_from_fs2000dps_to_mdps(int16_t lsb)
{
  return ((float)lsb * 70.0f);
}

      
      
      
      
int32_t asm330lhh_angular_rate_raw_get(SPI_HandleTypeDef* hspi, uint8_t *buff)
{
  int32_t ret;
  ret = asm330lhh_read_reg(hspi, ASM330LHH_OUTX_L_G, buff, 6);
  return ret;
}


int32_t asm330lhh_read_reg(SPI_HandleTypeDef* hspi, uint8_t reg, uint8_t* data,uint16_t len)
{
  if (hspi == &hspi2)
  {
    reg |= 0x80;
    HAL_GPIO_WritePin(SPI2_CSN_GPIO_Port, SPI2_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, &reg, 1, 1000);
    HAL_SPI_Receive(hspi, data, len, 1000);
    HAL_GPIO_WritePin(SPI2_CSN_GPIO_Port, SPI2_CSN_Pin, GPIO_PIN_SET);
  }
   return 0;
}











static int32_t platform_write(SPI_HandleTypeDef* hspi, uint8_t reg, uint8_t *data,uint16_t len)

{
   if (hspi == &hspi2)
  {
    HAL_GPIO_WritePin(SPI2_CSN_GPIO_Port, SPI2_CSN_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(hspi, &reg, 1, 1000);
    HAL_SPI_Transmit(hspi, data, len, 1000);
    HAL_GPIO_WritePin(SPI2_CSN_GPIO_Port, SPI2_CSN_Pin, GPIO_PIN_SET);
  }
  
  return 0;
}

