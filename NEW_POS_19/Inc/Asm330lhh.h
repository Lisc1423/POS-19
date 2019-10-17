#ifndef __Asm330lhh_H
#define __Asm330lhh_H
#ifdef __cplusplus
 extern "C" {
#endif
#include  "stdint.h" 
   

#define ASM330LHH_OUTX_L_G                     0x22U
#define ASM330LHH_OUTX_H_G                     0x23U
#define ASM330LHH_OUTY_L_G                     0x24U
#define ASM330LHH_OUTY_H_G                     0x25U
#define ASM330LHH_OUTZ_L_G                     0x26U
#define ASM330LHH_OUTZ_H_G                     0x27U 




#define SPI2_CSN_Pin GPIO_PIN_13
#define SPI2_CSN_GPIO_Port GPIOC
#define SPI2_MOSI_Pin GPIO_PIN_3
#define SPI2_MOSI_GPIO_Port GPIOC
#define SPI2_MISO_Pin GPIO_PIN_2
#define SPI2_MISO_GPIO_Port GPIOC
#define SPI2_SCK_Pin GPIO_PIN_13
#define SPI2_SCK_GPIO_Port GPIOB

   typedef union{
  int16_t i16bit[3];
  uint8_t u8bit[6];
} axis3bit16_t;   

extern axis3bit16_t data_raw_angular_rate;
extern float angular_rate_mdps[3];
  void get_anglespeed();
  float asm330lhh_from_fs2000dps_to_mdps(int16_t lsb);
  int32_t asm330lhh_angular_rate_raw_get(SPI_HandleTypeDef* hspi, uint8_t *buff);
  int32_t asm330lhh_read_reg(SPI_HandleTypeDef* hspi, uint8_t reg, uint8_t* data,uint16_t len);
  
  
  static int32_t platform_write(SPI_HandleTypeDef* hspi, uint8_t reg, uint8_t *data,uint16_t len);
   
   
   
#ifdef __cplusplus
}
#endif
#endif /* __Asm330lhh_H */





















