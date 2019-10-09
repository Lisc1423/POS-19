#ifndef __ASM330_H
#define __ASM330_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "main.h"

#include "spi.h"
#include "usart.h"
#include "gpio.h"
     
#define ASM330_CS_SET     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
#define ASM330_CS_RESET      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

/*********************************************************************************************************
**	陀螺仪控制数据定义
*********************************************************************************************************/
#define ASM330_STARTUP_DELAY	0.05 /* sec */

/* The MSB for the spi commands */
#define ASM330_SENSOR_DATA	0x20
#define ASM330_WRITE_DATA		0x40
#define ASM330_READ_DATA		0x80

/* Memory register map */
#define ASM330_RATE1			0x00	// Rate Registers
#define ASM330_TEMP1			0x02	// Temperature Registers
#define ASM330_LOCST1			0x04	// Low CST Memory Registers
#define ASM330_HICST1			0x06	// High CST Memory Registers
#define ASM330_QUAD1			0x08	// Quad Memory Registers
#define ASM330_FAULT1			0x0A	// Fault Registers
#define ASM330_PID1			0x0C	// Part ID Register 1
#define ASM330_SNH			0x0E	// Serial Number Registers, 4 bytes
#define ASM330_SNL			0x10

/* Check bits */
#define ASM330_P				0x01	// Parity bit
#define ASM330_CHK			0x02	
#define ASM330_CST			0x04
#define ASM330_PWR			0x08
#define ASM330_POR			0x10
#define ASM330_NVM			0x20
#define ASM330_Q				0x40
#define ASM330_PLL			0x80
#define ASM330_UV				0x100
#define ASM330_OV				0x200
#define ASM330_AMP			0x400
#define ASM330_FAIL			0x800

#define ASM330_WRERR_MASK		(0x7 << 29)
#define ASM330_GET_ST(a)		((a >> 26) & 0x3)  // Status bits



/*********************************************************************************************************
**	陀螺仪控制函数声明
*********************************************************************************************************/
uint8_t SPI_Read(uint8_t* data,uint8_t bytesNumber);
uint8_t SPI_Write(uint8_t *data,uint8_t bytesNumber);
uint8_t ASM330_ParityBit(uint32_t data);
uint8_t ASM330_Init(void);
int16_t ASM330_Data(void);
uint16_t ASM330_GetRegisterValue(uint8_t regAddress);
void ASM330_SetRegisterValue(uint8_t regAddress, uint16_t regData);
uint8_t ASM330_GetTemperature(void);
     
     
     
#ifdef __cplusplus
}
#endif
#endif