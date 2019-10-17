#include "as5047p.h"
#include "spi.h"
#include "cmd.h"
#include "imitate_spi.h"


//!  ??spi
    //static uint16_t Count_PARC(uint16_t data);
    //static uint16_t Command(uint16_t address,uint8_t read);
    //static uint16_t Write_frame(uint16_t data);
    //
    //uint16_t Read_Reg1(uint16_t reg){
    //  uint16_t command=0;
    //  uint16_t result=0;
    //  uint16_t err;
    //  //uint8_t result[2]={0};
    //  //uint8_t command[2]={0x7F,0xFE};
    //  
    //  command=Command(0x01,1);
    //  Set_CSN1(0);
    //  HAL_SPI_Transmit(&SPI_AS1,(uint8_t *)&command,1,100);
    //  Set_CSN1(1);
    //  
    //  command=Command(reg,1);
    //  Set_CSN1(0);
    //  HAL_SPI_TransmitReceive(&SPI_AS1,(uint8_t *)&command,(uint8_t *)&err,1,100);
    //  Set_CSN1(1);
    //  
    //  Set_CSN1(0);
    //  HAL_SPI_Receive(&SPI_AS1,(uint8_t *)&result,1,100);
    //  Set_CSN1(1);
    //  return result;
    //}
    //uint16_t Read_Reg2(uint16_t reg){
    //  uint16_t command=0;
    //  uint16_t result=0;
    //  uint16_t err;
    //  //uint8_t result[2]={0};
    //  //uint8_t command[2]={0x7F,0xFE};
    //  
    //  command=Command(0x01,1);
    //  Set_CSN2(0);
    //  HAL_SPI_Transmit(&SPI_AS2,(uint8_t *)&command,1,100);
    //  Set_CSN2(1);
    //  
    //  command=Command(reg,1);
    //  Set_CSN2(0);
    //  HAL_SPI_TransmitReceive(&SPI_AS2,(uint8_t *)&command,(uint8_t *)&err,1,100);
    //  Set_CSN2(1);
    //  
    //  Set_CSN2(0);
    //  HAL_SPI_Receive(&SPI_AS2,(uint8_t *)&result,1,100);
    //  Set_CSN2(1);
    //
    //  return result;
    //}
    //
    //uint16_t as5047p_Get_Position1(){
    //  uint16_t raw_data=0;
    //  uint16_t position=0;
    //  raw_data=Read_Reg1(0x3FFF);
    //  if(raw_data&(1<<14)){
    //    return 0xFFFF;
    //  }
    //  position=raw_data&0x3FFF;
    //  return position;
    //}
    //uint16_t as5047p_Get_Position2(){
    //  uint16_t raw_data=0;
    //  uint16_t position=0;
    //  raw_data=Read_Reg2(0x3FFF);
    ////  if(raw_data&(1<<14)){
    ////    return 0xFFFF;
    ////  }
    //  position=raw_data&0x3FFF;
    //  //uprintf("%d",raw_data);
    //  return position;
    //}
    //
    //
    //float Now_Position=0;
    //float Last_Position=0;
    //float Now_Speed=0;
    //int Init_Position=0;
    //void AS5047p_Get()
    //{ 
    //  
    //    //Now_Position = (float)(((int)as5047p_Get_Position() + (int)Init_Position) % AS5047PMAXPOS);
    //
    //  Now_Speed = Now_Position - Last_Position;
    //  
    //  while(Now_Speed > AS5047PMAXPOS/2)
    //    Now_Speed-=AS5047PMAXPOS;
    //  while(Now_Speed < -AS5047PMAXPOS/2)
    //    Now_Speed+=AS5047PMAXPOS;
    //}
    //
    //
    //uint16_t Write_Reg(uint16_t reg,uint16_t data){
    //  uint16_t command=0;
    //  uint16_t err;
    //  uint16_t frame;
    //  
    //  command=Command(0x01,1);//´íÎó¼Ä´æÆ÷
    //  Set_CSN2(0);
    //  HAL_SPI_Transmit(&SPI_AS2,(uint8_t *)&command,1,100);
    //  Set_CSN2(1);
    //  
    //  command=Command(reg,0);//Ð´µÄµØÖ·
    //  Set_CSN2(0);
    //  HAL_SPI_TransmitReceive(&SPI_AS2,(uint8_t *)&command,(uint8_t *)&err,1,100);
    //  Set_CSN2(1);
    //  
    //  Set_CSN2(0);//Ð´µÄÄÚÈÝ
    //  frame=Write_frame(data);//Ð´µÄÄÚÈÝ
    //  HAL_SPI_Transmit(&SPI_AS2,(uint8_t *)&frame,1,100);
    //  Set_CSN2(1);
    //  return err;
    //}
    //uint16_t as5047p_Write_Position(uint16_t data){
    //  uint16_t raw_data=0;
    //  uint16_t position=0;
    //  raw_data=Write_Reg(0x0003,data);
    //  if(raw_data&(1<<14)){
    //    return 0xFFFF;
    //  }
    //  position=raw_data&0x3fff;
    //  return position;
    //}
    //
    //static uint16_t Count_PARC(uint16_t data){
    //  // ?§µ?
    //  int cnt=0;
    //  uint16_t temp=0;
    //  for(int i=0;i<15;++i){
    //    temp=(1<<i);
    //    if(data&temp){
    //      cnt++;
    //    }
    //  }
    //  if(cnt%2==0){
    //    return 0;
    //  }else{
    //    return temp<<1;
    //  }
    //}
    //static uint16_t Command(uint16_t address,uint8_t read){
    //  uint16_t command=0;
    //  command|=address;
    //  command|=(read<<14);
    //  command|=Count_PARC(command);
    //  return command;
    //}
    //static uint16_t Write_frame(uint16_t data){
    //  uint16_t frame=0;
    //  frame|=data;
    //  frame|=(0<<14);
    //  frame|=Count_PARC(frame);
    //  return frame;
    //}
    //
//! ??spi




//??spi

uint8_t readBuffer[2]={1,1};
uint8_t writeBuffer1[2]={0x40,0x01};
uint8_t writeBuffer2[2]={0xff,0xff};
uint16_t ias5047p_Get_Position_x()
{
    ispi1_write_read(writeBuffer2, readBuffer,2);
    uint16_t now_position=(uint16_t)((readBuffer[0]&0x3f)*256+readBuffer[1]);
    return now_position;
}
uint16_t ias5047p_Get_Position_y()
{
    ispi3_write_read(writeBuffer2, readBuffer,2);
    uint16_t now_position=(uint16_t)((readBuffer[0]&0x3f)*256+readBuffer[1]);
    return now_position;
}