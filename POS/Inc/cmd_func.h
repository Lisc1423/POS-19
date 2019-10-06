#ifndef __cmd_func_H
#define __cmd_func_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"
#include "main.h"
#include "usart.h"
#include "cmd.h"
#include "stdlib.h"
#include "math.h"
#include "calculate.h"
#include "encoder.h"
   
void cmd_hello_func(int argc,char *argv[]);  
void cmd_read_func(int argc,char *argv[]);
void cmd_check_func(int argc,char *argv[]);
void cmd_modify_L_func(int argc,char *argv[]);
void cmd_modify_D_func(int argc,char *argv[]);
void cmd_reset_func(int argc,char *argv[]);
void cmd_read_encoder_func(int argc,char *argv[]);
void cmd_change_time_func(int argc,char *argv[]);
void cmd_send_wave_func(int argc,char *argv[]);
void cmd_setxy_func(int argc,char *argv[]);
void cmd_show_func(int argc,char *argv[]);
#ifdef __cplusplus
}
#endif
#endif /*__ cmd_func_H */