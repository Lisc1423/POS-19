#include "calculate.h"
#include "encoder.h"
#include "main.h"
#include "ASM330.h"
#include "as5047p.h"

typedef struct  Position
{
  int cnt_x;
  int cnt_y;
  float angle_x;
  float angle_y;
}Position;  
















/****************************parameter table***************************/

//LX,LY:全向轮中心距参考点垂直距离

//kx_center,ky_center:LX，LY修正项

//X_diameter,y_diameter:全向轮直径修正参数

//X,Y,thta,dthta:XY为编码器移动距离，thta当前偏航角

//dx,dy:世界坐标系下位移

/***********************************************************************/
float kx_center = 83,ky_center = 325;
float X_diameter = 1.056604,y_diameter = 1.037778;
float asm_offset_cnt = 0;


float calcul_dx(float thta,float d_thta,float X,float Y)
{
  
  float Ly=ky_center;
  float Lx=kx_center;
  float s,c;
  s=sin(thta);
  c=cos(thta);    
  float dx =  -Y*s + X*c + Ly*s*d_thta - Lx*c*d_thta;
  return dx;
}

float calcul_dy(float thta,float d_thta,float X,float Y)
{
  
  float Ly=ky_center;
  float Lx=kx_center;
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
  
  float x = encoder.encoderX_dir*encoder.X*50.5*PI/2048;                //2048线，周长50.5*PI
  float y = encoder.encoderY_dir*encoder.Y*50.5*PI/2048;
  
  x *= X_diameter;                                //对直径的修正
  y *= y_diameter; 

  //***********************计算x y th *****************************************//
  //float dth = calcul_dth();
  float dx = calcul_dx(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);                                    //  dth改
  float dy = calcul_dy(triangle.angle*PI/180,(triangle.angle-triangle.lastangle)*PI/180,x,y);

  
  triangle.x += dx;
  triangle.y += dy;  
  //triangle.angle += dth;                                                                            //todo为新pcb加入内容


  triangle.lastangle=triangle.angle;                    //用于计算dthta                              //!红色备注为新pcb删除内容
  triangle.angle=-inputangle;                           //成电陀螺仪 顺时针为正，取逆时针为正           //!
  

  
  triangle.showangle=angle_toshow(-inputangle);                             //输出角度范伟【-180.180】              //!
}

float angle_toshow(float angle)
{
  float showangle=0;
  showangle=angle;
  while(showangle>180||showangle<-180)
  {
    if(showangle>180)showangle-=360;
    if(showangle<=-180)showangle+=360;
  }
  return showangle;
}
