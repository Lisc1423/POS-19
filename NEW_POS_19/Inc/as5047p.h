#ifndef __as5047p_H
#define __as5047p_H
#ifdef __cplusplus
 extern "C" {
#endif
     
#include "spi.h"
   
   
   
#define HALL1_Pin GPIO_PIN_3
#define HALL1_GPIO_Port GPIOA
#define HALL1_EXTI_IRQn EXTI3_IRQn
#define HALL2_Pin GPIO_PIN_4
#define HALL2_GPIO_Port GPIOA
#define HALL2_EXTI_IRQn EXTI4_IRQn
#define HALL3_Pin GPIO_PIN_5
#define HALL3_GPIO_Port GPIOA
#define HALL3_EXTI_IRQn EXTI9_5_IRQn
#define CSN_MAG_Pin GPIO_PIN_5
#define CSN_MAG_GPIO_Port GPIOC
#define OLED_CSN_Pin GPIO_PIN_10
#define OLED_CSN_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_11
#define OLED_DC_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_12
#define OLED_RES_GPIO_Port GPIOB
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOD
#define KEY_EXTI_IRQn EXTI2_IRQn                //£¡´ýÉ¾¸Ä
   
   
   
   
   
   

#define AS5047PMAXPOS 16384
     
     
uint16_t as5047p_Get_Position();
uint16_t as5047p_Write_Position(uint16_t data);
#ifdef __cplusplus
}
#endif
#endif /*__ as5047p_H */