#include "calculate.h"
#include "encoder.h"
#include "main.h"
#include "ASM330.h"


/****************************parameter table***************************/

//LX,LY:全向轮中心距参考点垂直距离

//k1,k2:LX，LY修正项

//k3,k4:全向轮直径修正参数

//X,Y,thta,dthta:XY为编码器移动距离，thta当前偏航角

//dx,dy:世界坐标系下位移

/***********************************************************************/
int encoderX_dir=1;
int encoderY_dir=1;
float k1 = 83,k2 = 325;
float k3 = 1.056604,k4 = 1.037778;
float asm_offset_cnt = 0;
//ANG:1.020933  成电黑匣子陀螺仪校准系数


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

//***********************计算两个编码器位移*****************************************//
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
  
  float x = encoderX_dir*encoder.X*50.5*PI/2048;                //2048线，周长50.5*PI
  float y = encoderY_dir*encoder.Y*50.5*PI/2048;
  
  x *= k3;                                //对直径的修正
  y *= k4; 

//***********************计算x y th *****************************************//
  //float dth = calcul_dth();
  float dx = calcul_dx(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);                                    //  dth改
  float dy = calcul_dy(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);

  
  triangle.x += dx;
  triangle.y += dy;  
  //triangle.angle += dth;                                                                            //todo为新pcb加入内容


  triangle.lastangle=triangle.angle;                    //用于计算dthta                              //!红色备注为新pcb删除内容
  triangle.angle=-inputangle;                           //成电陀螺仪 顺时针为正，取逆时针为正           //!
  

  
  triangle.showangle=-inputangle;                             //输出角度范伟【-180.180】              //!
  //triangle.showangle=triangle.angle;                             //输出角度范伟【-180.180】              //todo
  while(triangle.showangle>180||triangle.showangle<-180)
  {
    if(triangle.showangle>180) triangle.showangle-=360;
    if(triangle.showangle<=-180) triangle.showangle+=360;
  }
  
}
