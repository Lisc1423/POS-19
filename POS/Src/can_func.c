#include "can_func.h"
#include "can.h"
#include "gpio.h"
#include "usart.h"
#include "main.h"
#include <stdlib.h>



//void callback(CanRxMsgTypeDef* pRxMsg)
//{
//  int i;
//  for(i=0;i<8;i++)
//  {
//    can_RX_data.ch[i]=pRxMsg->Data[i];
//    //uprintf("receive %x ",can_RX_data.ch[i]);
//  }
//  //uprintf("\r\n\r\n");
//  uprintf("ID=%x    ",pRxMsg->StdId);
//  uprintf("receive %lf\r\n\r\n",can_RX_data.df);
//}


void getangle(CanRxMsgTypeDef* pRxMsg)
{
  static int cnt=0;
  static float init=0;
  static float sum=0;
  if(pRxMsg->DLC == 4)
  {    
    candata.u8_form[0] = pRxMsg->Data[0];    
    candata.u8_form[1] = pRxMsg->Data[1];
    candata.u8_form[2] = pRxMsg->Data[2];
    candata.u8_form[3] = pRxMsg->Data[3];
    
    inputangle =candata.float_form[0];
    if(cnt<100)
    {
      sum+=inputangle;
      cnt++;
      init=sum/cnt;
    }
    else if(cnt==100)
    {
      init=sum/100;
      cnt++;
    }
    inputangle=inputangle-init;    
  }
}


