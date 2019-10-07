#ifndef __encoder_H
#define __encoder_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"
#include "main.h"     
#include "tim.h"     

typedef struct Encoder
{
    float X;
    float Y;
}Encoder;  
extern Encoder encoder;
void encoder_init(void);      
     
extern int encoderX_dir;
extern int encoderY_dir;
        
#ifdef __cplusplus
}
#endif
#endif /*__ encoder_H */
