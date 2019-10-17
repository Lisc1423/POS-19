#include "calculate.h"
#include "encoder.h"
#include "main.h"
#include "ASM330.h"


/****************************parameter table***************************/

//LX,LY:ȫ�������ľ�ο��㴹ֱ����

//k1,k2:LX��LY������

//k3,k4:ȫ����ֱ����������

//X,Y,thta,dthta:XYΪ�������ƶ����룬thta��ǰƫ����

//dx,dy:��������ϵ��λ��

/***********************************************************************/
int encoderX_dir=1;
int encoderY_dir=1;
float k1 = 83,k2 = 325;
float k3 = 1.056604,k4 = 1.037778;
float asm_offset_cnt = 0;
//ANG:1.020933  �ɵ��ϻ��������У׼ϵ��


float calcul_dx(float thta,float d_thta,float X,float Y)
{
  
  float Ly=k2;
  float Lx=k1;
  float s,c;
  s=sin(thta);
  c=cos(thta);    
  float dx =  -Y*s + X*c + Ly*s*d_thta - Lx*c*d_thta;
  return dx;
}

float calcul_dy(float thta,float d_thta,float X,float Y)
{
  
  float Ly=k2;
  float Lx=k1;
  float s,c;
  s=sin(thta);
  c=cos(thta);    
  float dy =  Y*c + X*s - Ly*c*d_thta - Lx*s*d_thta;      
  return dy;
}

float calcul_dth()
{
    float d_thta;
    d_thta = ASM330_Data();
    d_thta -= asm_offset_cnt /500;
    d_thta /= 80.0;
    d_thta *= (PI/180)*0.01;
    return d_thta;
}




void calcul_XY()
{

//***********************��������������λ��*****************************************//
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
  
  float x = encoderX_dir*encoder.X*50.5*PI/2048;                //2048�ߣ��ܳ�50.5*PI
  float y = encoderY_dir*encoder.Y*50.5*PI/2048;
  
  x *= k3;                                //��ֱ��������
  y *= k4; 

//***********************����x y th *****************************************//
  //float dth = calcul_dth();
  float dx = calcul_dx(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);                                    //  dth��
  float dy = calcul_dy(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);

  
  triangle.x += dx;
  triangle.y += dy;  
  //triangle.angle += dth;                                                                            //todoΪ��pcb��������


  triangle.lastangle=triangle.angle;                    //���ڼ���dthta                              //!��ɫ��עΪ��pcbɾ������
  triangle.angle=-inputangle;                           //�ɵ������� ˳ʱ��Ϊ����ȡ��ʱ��Ϊ��           //!
  

  
  triangle.showangle=-inputangle;                             //����Ƕȷ�ΰ��-180.180��              //!
  //triangle.showangle=triangle.angle;                             //����Ƕȷ�ΰ��-180.180��              //todo
  while(triangle.showangle>180||triangle.showangle<-180)
  {
    if(triangle.showangle>180) triangle.showangle-=360;
    if(triangle.showangle<=-180) triangle.showangle+=360;
  }
  
}
