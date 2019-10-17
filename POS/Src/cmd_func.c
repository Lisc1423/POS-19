#include "cmd_func.h"
#include "can_func.h"
#include "flash.h"
#include "tim.h"
#include "calculate.h"


extern Triangle triangle;
extern Flag flag;
extern int time;

void cmd_hello_func(int argc,char *argv[])  //hello
{
  uprintf("HELLO!");
}


void cmd_version_func(int argc,char *argv[])  //vesion
{
  uprintf("VESION 1.0 !");
}

void cmd_reset_func(int argc,char *argv[])  //vesion                  //!��δʹ�ù� �����
{
  __set_FAULTMASK(1);   //STM32���������λ  
 NVIC_SystemReset(); 
}

void cmd_default_func(int argc,char *argv[])  //vesion                  //!��δʹ�ù� �����
{
k1 = 83;
k2 = 325;
k3 = 1.056604;
k4 = 1.037778;
time=5;
//!�ڴ˴�����canidĬ��ֵ
uprintf("���� k1 = %f  k2 = %f  k3=%f  k4=%f   \r\n", k1,k2,k3,k4);
uprintf("����ʱ��time=%d   \r\n", time);
 
}
/*       
*       FLAG
*       ���ܣ�����readflag �����������λ����Ϣ  
*       ������read [0/1]  ��1�򿪣��������رգ�
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
*       ���ܣ�����encoderflag �������������������Ϣ  
*       ������ encoder [0/1] ��1�򿪣��������رգ�
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
*       ���ܣ�����senwaveflag ����������ʾ����  
*       ������ wave [0/1] ��1�򿪣��������رգ�
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
*       ���ܣ��޸Ķ�λ�ο���ඨλģ����ȫ���״�ֱ����
*       ������modify_L k1 k2 
*/
void cmd_modify_L_func(int argc,char *argv[])
{

  k1 = atof(argv[1]);
  k2 = atof(argv[2]);  
  
  flash_data[0]=k1;
  flash_data[1]=k2;
  write_prams();
  uprintf("ϵ���Ѿ��޸ģ� k1 = %f  k2 = %f  \r\n",k1,k2);
  
}
/*       PARAM
*       ���ܣ��޸�����ֱ���ߴ�
*       ������modify_D k3 k4 
*/
void cmd_modify_D_func(int argc,char *argv[])
{

  k3 = atof(argv[1]);
  k4 = atof(argv[2]);  
  
  flash_data[2]=k3;
  flash_data[3]=k4;
  write_prams();
  uprintf("ϵ���Ѿ��޸ģ� k3 = %f  k4 = %f  \r\n",k3,k4);
}


void cmd_modify_CANID_func(int argc,char *argv[])
{

  CANSEND_ID = (uint32_t)atof(argv[1]);
  CANRECV_ID = (uint32_t)atof(argv[2]);  
  
  flash_data[5]=CANSEND_ID;
  flash_data[6]=CANRECV_ID;
  write_prams();
  uprintf("ϵ���Ѿ��޸ģ� CANSEND_ID = %x  CANRECV_ID = %x  \r\n",CANSEND_ID,CANRECV_ID);
}

/*       PARAM
*       ���ܣ��޸Ĳ���ʱ��
*       ������time value
*/
void cmd_change_time_func(int argc,char *argv[]) 
{
  time=atoi(argv[1]);
  
  flash_data[4]=(float)time;
  write_prams();
  uprintf("����ʱ���޸ģ�%d\r\n",time);
}
/*       SET
*       ���ܣ�set xy
*       ������setxy x y
*/
void cmd_setxy_func(int argc,char *argv[])                                                          //!������Ƕ�
{
  triangle.x= atof(argv[1]);
  triangle.y = atof(argv[2]);
  //triangle.angle = atof(argv[3]);
  uprintf("xy�Ѿ��޸ģ�x = %f  y = %f  \r\n", triangle.x, triangle.y);
}
/*    CHECK
*       ���ܣ�����ƶ��Ƿ�λ
*       ������check [1/2/3] value (�Ƕȷ�ΧΪ��-180��180��)
*/
void cmd_check_func(int argc,char *argv[])//
{
  float target = atof(argv[2]);
  uprintf("start check data\r\n");
  
  if(atoi(argv[1])==1)
  {
    if(triangle.x-target<=2||triangle.x-target>=-2)
      uprintf("xֵ����Ŀ��\r\n");
    else
      uprintf("xƫ��Ϊ%f\r\n",triangle.x-target);
  }
  else if(atoi(argv[1])==2)
  {
    if(triangle.y-target<=2||triangle.y-target>=-2)
      uprintf("yֵ����Ŀ��\r\n");
    else
      uprintf("yƫ��Ϊ%f\r\n",triangle.y-target);
  }
  else if(atoi(argv[1])==3)
  {
    if(triangle.showangle-target<=0.02||triangle.showangle-target>=-0.02)
      uprintf("angleֵ����Ŀ��\r\n");
    else
      uprintf("angleƫ��Ϊ%f\r\n",triangle.showangle-target);
  }
  else 
    uprintf("������1/2/3");
} 
/*      SHOW
*       ���ܣ������param
*       ������check [1/2/3] value (�Ƕȷ�ΧΪ��-180��180��)
*/
void cmd_show_func(int argc,char *argv[])
{
  uprintf("���� k1 = %f  k2 = %f  k3=%f  k4=%f   \r\n", k1,k2,k3,k4);
  uprintf("����ʱ��time=%d   \r\n", time);
}

void cmd_encoderXdir_func(int argc,char *argv[])
{
  HAL_Delay(1500);
  int dir=0;
  float cnt=0;
  for(int i=0;i<20;i++)
  {
  TIM4->CNT=0;
  HAL_Delay(50);
  if(TIM4->CNT >= 30000)
    cnt = (float)TIM4->CNT-65536;
  else
    cnt = (float)TIM4->CNT; 
  if(cnt>0)
    dir +=1;
  if(cnt<0)
    dir -=1;
  } 
  if(dir>=0) 
  encoderX_dir = 1;
  else 
  encoderX_dir = -1;  
}

void cmd_encoderYdir_func(int argc,char *argv[])
{
  HAL_Delay(1500);
  int dir=0;
  float cnt=0;
  for(int i=0;i<20;i++)
  {
  TIM4->CNT=0;
  HAL_Delay(50);
  if(TIM4->CNT >= 30000)
    cnt = (float)TIM4->CNT-65536;
  else
    cnt = (float)TIM4->CNT; 
  if(cnt>0)
    dir +=1;
  if(cnt<0)
    dir -=1;
  } 
  if(dir>=0) 
  encoderY_dir = 1;
  else 
  encoderY_dir = -1;  
}