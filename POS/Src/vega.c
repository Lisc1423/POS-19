#include "vega.h"
#include "usart.h"

#define PI 3.141596

static int *g_vega_pos_x,*g_vega_pos_y;
static float *g_vega_angle;

float vega_yaw=0;
float vega_yaw_init=0;
int yaw_cnt=0;
float sum_yaw=0;

void vega_msg_rcv_callback(CanRxMsgTypeDef *can_rx_msg);

/* 函数名：int vega_init()
* 功能：初始化vega
*       在外部使用该模块时，将外部的x，y，angle变量指针传入该文件，
*       以实现对全场坐标的实时更新
* 参数：int *p_pos_x,存储x坐标的变量的指针
*       int *p_pos_y,存储y坐标的变量的指针
*       float *p_angle,存储角度的变量的指针
* 返回值：1,初始化成功
*         -1,初始化失败
*/
int vega_init(int *p_pos_x,int *p_pos_y,float *p_angle){
    
    g_vega_pos_x = p_pos_x;
    g_vega_pos_y = p_pos_y;
    g_vega_angle = p_angle;
   
    /*
    uprintf(CMD_USART,"g_vega_angle=%f\r\n",g_vega_angle);
    uprintf(CMD_USART,"g_vega_pos_y=%f\r\n",g_vega_pos_y);
    uprintf(CMD_USART,"g_vega_pos_x=%f\r\n",g_vega_pos_x);
    */
    
    HAL_Delay(1000);
    
    return 1;
}

/* 函数名：void vege_msg_rc_callback()
* 功能：接收消息的回调函数
* 参数：接收消息的数据结构的指针
* 返回值：无
*/
void vega_msg_rcv_callback(CanRxMsgTypeDef *can_rx_msg){
    data_convert temp;
    static float vega_yaw_temp=0;
    //if(can_rx_msg->StdId == VEGA_CAN_ID){   //如果是VEGA的包
    if(can_rx_msg->DLC == 8){//8位的前四位是x,后四位是y，注意传来的int32位以小端方式存储，低位在低位
        temp.u8_form[0] = can_rx_msg->Data[0];
        temp.u8_form[1] = can_rx_msg->Data[1];
        temp.u8_form[2] = can_rx_msg->Data[2];
        temp.u8_form[3] = can_rx_msg->Data[3];
        //memcpy((void*)g_vega_pos_x,&temp.s32_form,4);//stm32也为小端存储，对应起来就好
        temp.u8_form[4] = can_rx_msg->Data[4];
        temp.u8_form[5] = can_rx_msg->Data[5];
        temp.u8_form[6] = can_rx_msg->Data[6];
        temp.u8_form[7] = can_rx_msg->Data[7];
        //chassis.g_vega_pos_x = temp.float_form[0];
        //chassis.g_vega_pos_y = temp.float_form[1];
        //memcpy((void*)g_vega_pos_y,&temp.s32_form,4);
    }else if(can_rx_msg->DLC == 4){
        temp.u8_form[0] = can_rx_msg->Data[0];
        temp.u8_form[1] = can_rx_msg->Data[1];
        temp.u8_form[2] = can_rx_msg->Data[2];
        temp.u8_form[3] = can_rx_msg->Data[3];
        //chassis.g_vega_angle = temp.float_form[0];
        vega_yaw_temp=temp.float_form[0];
        //memcpy((void*)g_vega_angle,&temp.float_form,4);  
    }
    //chassis.pos_x = chassis.g_vega_pos_x * 0.0001 * 0.81;
    //chassis.pos_y = - chassis.g_vega_pos_y * 0.0001 * 0.81;//这个地方全场定位y反了，注意！！！！
    //chassis.angle = - (chassis.g_vega_angle / 180.f) * PI;
    //vega_yaw = -(vega_yaw_temp / 180.f) * PI;
    if(yaw_cnt<100)
    {
      sum_yaw+=vega_yaw_temp;
      yaw_cnt++;
      vega_yaw_init=sum_yaw/yaw_cnt;
    }
    else if(yaw_cnt==100)
    {
      vega_yaw_init=sum_yaw/100;
      yaw_cnt++;
    }

    vega_yaw=vega_yaw_temp-vega_yaw_init;
    
    //uprintf(&huart2,"x = %f y = %f  angle = %f\r\n",chassis.pos_x,chassis.pos_y,chassis.angle);
}


/* 函数名：void vega_set_angle()
* 功能：设置vega角度
* 参数：float angle,需要设置的角度
* 返回值：1,设置成功
*         -1,设置失败
*/
int vega_set_angle(float angle){
    data_convert temp;
    temp.float_form[0] = angle;
    return can_send_msg(CMD_CAN_ID,temp.u8_form,4);
}


/* 函数名：void vega_set_pos()
* 功能：设置vega的x,y坐标
* 参数：int pos_x 需要设置的x坐标
*       int pos_y 需要设置的y坐标
* 返回值：1,设置成功
*         -1,设置失败
*/
int vega_set_pos(int pos_x,int pos_y){
    uint8_t send_data[8];
    //int 小端模式，低位存在低地址 
    send_data[0] = (uint8_t)(pos_x >> 0 * 8);
    send_data[1] = (uint8_t)(pos_x >> 1 * 8);
    send_data[2] = (uint8_t)(pos_x >> 2 * 8);
    send_data[3] = (uint8_t)(pos_x >> 3 * 8);
    send_data[4] = (uint8_t)(pos_y >> 0 * 8);
    send_data[5] = (uint8_t)(pos_y >> 1 * 8);
    send_data[6] = (uint8_t)(pos_y >> 2 * 8);
    send_data[7] = (uint8_t)(pos_y >> 3 * 8);
    return can_send_msg(CMD_CAN_ID,send_data,8);
}


/* 函数名：int vega_reset()
* 功能：软件复位vega
* 参数：无
* 返回值：1,复位成功
*         -1,复位失败
*/
int vega_reset(){
    uint8_t send_data[2];
    send_data[0] = 0x55;
    send_data[1] = 0xff;
    return can_send_msg(CMD_CAN_ID,send_data,2);
}

