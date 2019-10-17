#include "gpio.h"
#include "imitate_spi.h"
#include "usart.h"
#include "tim.h"

/*******************����ģ��spi********************/
//CPOL=0        CLK�͵�ƽ����
//CPHA=0       ��һ��ʱ���أ���ʱ�������أ��ɼ��ź�

/*iSPI1*/

#define iSPI1_CSN_Pin GPIO_PIN_15
#define iSPI1_CSN_GPIO_Port GPIOC
#define iSPI1_MOSI_Pin GPIO_PIN_7
#define iSPI1_MOSI_GPIO_Port GPIOA
#define iSPI1_MISO_Pin GPIO_PIN_6
#define iSPI1_MISO_GPIO_Port GPIOA
#define iSPI1_SCK_Pin GPIO_PIN_5
#define iSPI1_SCK_GPIO_Port GPIOA

#define iSPI1_CS_Enable() 	HAL_GPIO_WritePin(iSPI1_CSN_GPIO_Port, iSPI1_CSN_Pin, GPIO_PIN_RESET)//Ƭѡ�źŵ͵�ƽ��Ч
#define iSPI1_CS_Disable() 	HAL_GPIO_WritePin(iSPI1_CSN_GPIO_Port, iSPI1_CSN_Pin, GPIO_PIN_SET)
#define iSPI1_CLK_Enable() 	HAL_GPIO_WritePin(iSPI1_SCK_GPIO_Port, iSPI1_SCK_Pin, GPIO_PIN_SET                                                                                                                 )
#define iSPI1_CLK_Disable() 	HAL_GPIO_WritePin(iSPI1_SCK_GPIO_Port, iSPI1_SCK_Pin, GPIO_PIN_RESET)


uint8_t ispi1_write_read_byte(uint8_t writeBuffer)
{
  int i;
  uint8_t Buffer=0;
  for (i=7;i>=0;i--) 
  {   
    HAL_GPIO_WritePin(iSPI1_MOSI_GPIO_Port, iSPI1_MOSI_Pin, (GPIO_PinState)(writeBuffer&(1<<i)));//�Ӹ�λ7����λ0���д���д�� 
    //Delay(5);
    iSPI1_CLK_Enable();
    Delay(5);
    iSPI1_CLK_Disable();//�½�������
    GPIO_PinState temp=HAL_GPIO_ReadPin(iSPI1_MISO_GPIO_Port, iSPI1_MISO_Pin);
    Buffer = (Buffer <<1) | temp;   //�Ӹ�λ7����λ0���д��ж���
    Delay(5);
  }
  return Buffer;
}

void ispi1_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len)
{
  int i;
  iSPI1_CS_Enable();       //���豸ʹ����Ч��ͨ�ſ�ʼ
  Delay(10); 
  for (i=0; i<len; i++)
    readBuffer[i]=ispi1_write_read_byte(writeBuffer[i]);
  Delay(10);
  iSPI1_CS_Disable();
  Delay(10);
}


/*iSPI3*/
#define iSPI3_CSN_Pin GPIO_PIN_14
#define iSPI3_CSN_GPIO_Port GPIOC
#define iSPI3_MOSI_Pin GPIO_PIN_12
#define iSPI3_MOSI_GPIO_Port GPIOC
#define iSPI3_MISO_Pin GPIO_PIN_11
#define iSPI3_MISO_GPIO_Port GPIOC
#define iSPI3_SCK_Pin GPIO_PIN_10
#define iSPI3_SCK_GPIO_Port GPIOC

#define iSPI3_CS_Enable() 	HAL_GPIO_WritePin(iSPI3_CSN_GPIO_Port, iSPI3_CSN_Pin, GPIO_PIN_RESET)//Ƭѡ�źŵ͵�ƽ��Ч
#define iSPI3_CS_Disable() 	HAL_GPIO_WritePin(iSPI3_CSN_GPIO_Port, iSPI3_CSN_Pin, GPIO_PIN_SET)
#define iSPI3_CLK_Enable() 	HAL_GPIO_WritePin(iSPI3_SCK_GPIO_Port, iSPI3_SCK_Pin, GPIO_PIN_SET                                                                                                                 )
#define iSPI3_CLK_Disable() 	HAL_GPIO_WritePin(iSPI3_SCK_GPIO_Port, iSPI3_SCK_Pin, GPIO_PIN_RESET)
uint8_t ispi3_write_read_byte(uint8_t writeBuffer)
{
  int i;
  uint8_t Buffer=0;
  for (i=7;i>=0;i--) 
  {   
    HAL_GPIO_WritePin(iSPI3_MOSI_GPIO_Port, iSPI3_MOSI_Pin, (GPIO_PinState)(writeBuffer&(1<<i)));//�Ӹ�λ7����λ0���д���д�� 
    //Delay(5);
    iSPI3_CLK_Enable();
    Delay(5);
    iSPI3_CLK_Disable();//�½�������
    GPIO_PinState temp=HAL_GPIO_ReadPin(iSPI3_MISO_GPIO_Port, iSPI3_MISO_Pin);
    Buffer = (Buffer <<1) | temp;   //�Ӹ�λ7����λ0���д��ж���
    Delay(5);
  }
  return Buffer;
}

void ispi3_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len)
{
  int i;
  iSPI3_CS_Enable();       //���豸ʹ����Ч��ͨ�ſ�ʼ
  Delay(10); 
  for (i=0; i<len; i++)
    readBuffer[i]=ispi3_write_read_byte(writeBuffer[i]);
  Delay(10);
  iSPI3_CS_Disable();
  Delay(10);
}




/*********************
 
#define iSPI2_CSN_Pin GPIO_PIN_13
#define iSPI2_CSN_GPIO_Port GPIOC
#define iSPI2_MOSI_Pin GPIO_PIN_3
#define iSPI2_MOSI_GPIO_Port GPIOC
#define iSPI2_MISO_Pin GPIO_PIN_2
#define iSPI2_MISO_GPIO_Port GPIOC
#define iSPI2_SCK_Pin GPIO_PIN_13
#define iSPI2_SCK_GPIO_Port GPIOB

#define iSPI2_CS_Enable() 	HAL_GPIO_WritePin(iSPI2_CSN_GPIO_Port, iSPI2_CSN_Pin, GPIO_PIN_RESET)//Ƭѡ�źŵ͵�ƽ��Ч
#define iSPI2_CS_Disable() 	HAL_GPIO_WritePin(iSPI2_CSN_GPIO_Port, iSPI2_CSN_Pin, GPIO_PIN_SET)
#define iSPI2_CLK_Enable() 	HAL_GPIO_WritePin(iSPI2_SCK_GPIO_Port, iSPI2_SCK_Pin, GPIO_PIN_SET                                                                                                                 )
#define iSPI2_CLK_Disable() 	HAL_GPIO_WritePin(iSPI2_SCK_GPIO_Port, iSPI2_SCK_Pin, GPIO_PIN_RESET)
uint8_t ispi2_write_read_byte(uint8_t writeBuffer)
{
  int i;
  uint8_t Buffer=0;
  for (i=7;i>=0;i--) 
  {   
    HAL_GPIO_WritePin(iSPI2_MOSI_GPIO_Port, iSPI2_MOSI_Pin, (GPIO_PinState)(writeBuffer&(1<<i)));//�Ӹ�λ7����λ0���д���д�� 
    //Delay(5);
    iSPI2_CLK_Enable();
    Delay(5);
    iSPI2_CLK_Disable();//�½�������
    GPIO_PinState temp=HAL_GPIO_ReadPin(iSPI2_MISO_GPIO_Port, iSPI2_MISO_Pin);
    Buffer = (Buffer <<1) | temp;   //�Ӹ�λ7����λ0���д��ж���
    Delay(5);
  }
  return Buffer;
}

void ispi2_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len)
{
  int i;
  iSPI2_CS_Enable();       //���豸ʹ����Ч��ͨ�ſ�ʼ
  Delay(10); 
  for (i=0; i<len; i++)
    readBuffer[i]=ispi2_write_read_byte(writeBuffer[i]);
  Delay(10);
  iSPI2_CS_Disable();
  Delay(10);
}
 */