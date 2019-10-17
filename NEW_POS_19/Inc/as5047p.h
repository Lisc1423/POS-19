#ifndef __as5047p_H
#define __as5047p_H
#ifdef __cplusplus
 extern "C" {
#endif
#include  "stdint.h" 
   
uint16_t ias5047p_Get_Position_y();
uint16_t ias5047p_Get_Position_x();
      
//!硬件spi
   /* #define AS5047PMAXPOS 16384    
    uint16_t as5047p_Get_Position1();
    uint16_t as5047p_Get_Position2();
    uint16_t as5047p_Write_Position(uint16_t data);*/
//!硬件spi

#ifdef __cplusplus
}
#endif
#endif /*__ as5047p_H */