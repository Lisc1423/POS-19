#ifndef __can_func_H
#define __can_func_H
#ifdef __cplusplus
 extern "C" {
#endif
   
#include "stm32f4xx_hal.h"
#include "main.h"

void callback(CanRxMsgTypeDef* pRxMsg);


typedef union{
        char ch[8];
        uint8_t ui8[8];
        uint16_t ui16[4];
        int in[2];
        float fl[2];
        double df;
}can_change_msg;
   
void getangle(CanRxMsgTypeDef* pRxMsg);

   
 #ifdef __cplusplus
}
#endif
#endif /*__ can_func_H */