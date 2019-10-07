#include "cmd_func.h"
#include "flash.h"
extern Triangle triangle;
extern Flag flag;
extern int time;

void cmd_hello_func(int argc,char *argv[])  //hello
{
  uprintf("hello world");
}
/*       
*       FLAG
*       功能：设置readflag ：主函数输出位置信息  
*       参数：read [0/1]  （1打开，其余数关闭）
*/
void cmd_read_func(int argc,char *argv[])
{
  flag.read = atoi(argv[1]);
  if(flag.read == 1)
    uprintf("read OK\r\n");
  else 
    uprintf("read Stoped\r\n");
}
/*       FLAG
*       功能：设置encoderflag ：主函数输出编码器信息  
*       参数： encoder [0/1] （1打开，其余数关闭）
*/
void cmd_read_encoder_func(int argc,char *argv[])
{
  if(atoi(argv[1])==1)
  {
    uprintf("encoder OK\r\n");
    flag.encoder =1;
  }
  else
  {
    uprintf("encoder Stoped\r\n");
    flag.encoder =0;
  }
}
/*       FLAG
*       功能：设置senwaveflag ：主函数打开示波器  
*       参数： wave [0/1] （1打开，其余数关闭）
*/
void cmd_send_wave_func(int argc,char *argv[])    
{
  if(atoi(argv[1])==1)
  {
    uprintf("wave OK\r\n");
    flag.wave =1;
  }
  else
  {
    uprintf("wave Stoped\r\n");
    flag.wave =0;
  }  
}
/*       PARAM
*       功能：修改定位参考点距定位模块两全向伦垂直距离
*       参数：modify_L k1 k2 
*/
void cmd_modify_L_func(int argc,char *argv[])
{

  k1 = atof(argv[1]);
  k2 = atof(argv[2]);  
  
  flash_data[0]=k1;
  flash_data[1]=k2;
  write_prams();
  uprintf("系数已经修改： k1 = %f  k2 = %f  \r\n",k1,k2);
  
}
/*       PARAM
*       功能：修改两轮直径尺寸
*       参数：modify_D k3 k4 
*/
void cmd_modify_D_func(int argc,char *argv[])
{

  k3 = atof(argv[1]);
  k4 = atof(argv[2]);  
  
  flash_data[2]=k3;
  flash_data[3]=k4;
  write_prams();
  uprintf("系数已经修改： k3 = %f  k4 = %f  \r\n",k3,k4);
}
/*       PARAM
*       功能：修改采样时间
*       参数：time value
*/
void cmd_change_time_func(int argc,char *argv[]) 
{
  time=atoi(argv[1]);
  
  flash_data[4]=(float)time;
  write_prams();
  uprintf("采样时间修改：%d\r\n",time);
}
/*       SET
*       功能：reset pos
*       参数：reset
*/
void cmd_reset_func(int argc,char *argv[]) 
{
  uprintf("reset!\r\n");
  triangle.x = 0;
  triangle.y = 0;
  triangle.angle = 0;
}
/*       SET
*       功能：set xy
*       参数：setxy x y
*/
void cmd_setxy_func(int argc,char *argv[])
{
  triangle.x= atof(argv[1]);
  triangle.y = atof(argv[2]);
  uprintf("xy已经修改：x = %f  y = %f  \r\n", triangle.x, triangle.y);
}
/*    CHECK
*       功能：检查移动是否到位
*       参数：check [1/2/3] value (角度范围为【-180，180】)
*/
void cmd_check_func(int argc,char *argv[])//
{
  float target = atof(argv[2]);
  uprintf("start check data\r\n");
  
  if(atoi(argv[1])==1)
  {
    if(triangle.x-target<=2||triangle.x-target>=-2)
      uprintf("x值到达目标\r\n");
    else
      uprintf("x偏差为%f\r\n",triangle.x-target);
  }
  else if(atoi(argv[1])==2)
  {
    if(triangle.y-target<=2||triangle.y-target>=-2)
      uprintf("y值到达目标\r\n");
    else
      uprintf("y偏差为%f\r\n",triangle.y-target);
  }
  else if(atoi(argv[1])==3)
  {
    if(triangle.showangle-target<=0.02||triangle.showangle-target>=-0.02)
      uprintf("angle值到达目标\r\n");
    else
      uprintf("angle偏差为%f\r\n",triangle.showangle-target);
  }
  else 
    uprintf("请输入1/2/3");
} 
/*      SHOW
*       功能：输出个param
*       参数：check [1/2/3] value (角度范围为【-180，180】)
*/
void cmd_show_func(int argc,char *argv[])
{
  uprintf("参数 k1 = %f  k2 = %f  k3=%f  k4=%f   \r\n", k1,k2,k3,k4);
  uprintf("采样时间time=%d   \r\n", time);
}

