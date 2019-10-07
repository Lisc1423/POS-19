#include "calculate.h"
#include "encoder.h"
#include "main.h"


/****************************parameter table***************************/

//LX,LY:ȫ�������ľ�ο��㴹ֱ����

//k1,k2:LX��LY������

//k3,k4:ȫ����ֱ����������

//X,Y,thta,dthta:XYΪ�������ƶ����룬thta��ǰƫ����

//dx,dy:��������ϵ��λ��

/****************************������***************************/

float k1 = 0,k2 = 0;
float k3 = 1,k4 = 1;
//ANG:1.020933  �ɵ��ϻ��������У׼ϵ��


float calcul_dx(float thta,float d_thta,float X,float Y)
{
  
  float Ly=325+k2;
  float Lx=83+k1;
  float s,c;
  s=sin(thta);
  c=cos(thta);    
  float dx =  -Y*s + X*c + Ly*s*d_thta - Lx*c*d_thta;
  return dx;
}

float calcul_dy(float thta,float d_thta,float X,float Y)
{
  
  float Ly=325+k2;
  float Lx=83+k1;
  float s,c;
  s=sin(thta);
  c=cos(thta);    
  float dy =  Y*c + X*s - Ly*c*d_thta - Lx*s*d_thta;      
  return dy;
}

//float calcul_dth()

void calcul_XY()
{
  if(TIM4->CNT >= 30000)
    encoder.X = (float)TIM4->CNT-65536;
  else
    encoder.X = (float)TIM4->CNT;
  
  if(TIM3->CNT >= 30000)
    encoder.Y = (float)TIM3->CNT-65536;
  else
    encoder.Y = (float)TIM3->CNT;
  
  TIM3->CNT=0;
  TIM4->CNT=0;
  
  float x = encoder.X*50.5*PI/2048;                //2048�ߣ��ܳ�50.5*PI
  float y = encoder.Y*50.5*PI/2048;
  
  k3 = 1.056604;
  k4 = 1.037778;
  x *= k3;                                //��ֱ��������
  y *= k4; 
  
  triangle.lastangle=triangle.angle;                    //���ڼ���dthta
  triangle.angle=-inputangle;                           //�ɵ������� ˳ʱ��Ϊ����ȡ��ʱ��Ϊ��
  
  float dx = calcul_dx(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);
  float dy = calcul_dy(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,y,y);
  
  triangle.x += dx;
  triangle.y += dy;  
  
  triangle.showangle=-inputangle;                             //����Ƕȷ�ΰ��-180.180��
  while(triangle.showangle>180||triangle.showangle<-180)
  {
    if(triangle.showangle>180) triangle.showangle-=360;
    if(triangle.showangle<=-180) triangle.showangle+=360;
  }
  
}
