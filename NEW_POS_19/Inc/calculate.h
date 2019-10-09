#ifndef __calculate_H
#define __calculate_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"
#include "main.h"   
#include "math.h"
#include "usart.h"

#define PI 3.1415926535
     
typedef struct Triangle
{
    float x;
    float y;
    float angle;
    float lastangle;
    float showangle;
}Triangle;
extern Triangle triangle;

float calcul_dx(float thta,float d_thta,float X1,float X2);
float calcul_dy(float thta,float d_thta,float X1,float X2);
void calcul_XY();

extern float k1,k2;
extern float k3,k4;
extern int encoderX_dir;
extern int encoderY_dir;

#ifdef __cplusplus
}
#endif
#endif /*__ calculate_H */
