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
*       ���ܣ�reset pos
*       ������reset
*/
void cmd_reset_func(int argc,char *argv[]) 
{
  uprintf("reset!\r\n");
  triangle.x = 0;
  triangle.y = 0;
  triangle.angle = 0;
}
/*       SET
*       ���ܣ�set xy
*       ������setxy x y
*/
void cmd_setxy_func(int argc,char *argv[])
{
  triangle.x= atof(argv[1]);
  triangle.y = atof(argv[2]);
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

