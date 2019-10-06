/**
******************************************************************************
* File Name          : USART.c
* Description        : This file provides code for the configuration
*                      of the USART instances.
******************************************************************************
** This notice applies to any and all portions of this file
* that are not between comment pairs USER CODE BEGIN and
* USER CODE END. Other portions of this file, whether 
* inserted by the user or by software development tools
* are owned by their respective copyright owners.
*
* COPYRIGHT(c) 2019 STMicroelectronics
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN 0 */
uint8_t aRxBuffer[RXBUFFERSIZE];           //hal��ʹ�ô��ڽ��ջ���
char USART_RX_BUF[USART_REC_LEN];       //�Զ�����մ�ŵ�����
uint16_t USART_RX_STA=0;                   //����״̬��־�����յ�0x0d��0x0a����	
/* USER CODE END 0 */

UART_HandleTypeDef huart2;

/* USART2 init function */

void MX_USART2_UART_Init(void)
{
  
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  
}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  
  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */
    
    /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
    
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspInit 1 */
    
    /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  
  if(uartHandle->Instance==USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */
    
    /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
    
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
    
    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspDeInit 1 */
    
    /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
char uart_buffer[100 + 1];
void uprintf(char *fmt, ...)
{
  int size;
  
  va_list arg_ptr;
  
  va_start(arg_ptr, fmt);  
  
  size=vsnprintf(uart_buffer, 100 + 1, fmt, arg_ptr);
  va_end(arg_ptr);
  HAL_UART_Transmit(&huart2,(uint8_t *)uart_buffer,size,1000);
}

char s[22]={'b','y',16,6};
void send_wave(float arg1,float arg2,float arg3,float arg4){
  
  s[2]=16;  //length
  s[3]=6;   //pe
  s[20]='\r';
  s[21]='\n';
  memcpy(s+4,&arg1,sizeof(arg1));
  memcpy(s+8,&arg2,sizeof(arg1));
  memcpy(s+12,&arg3,sizeof(arg1));
  memcpy(s+16,&arg4,sizeof(arg1));
  HAL_UART_Transmit(&huart2,(uint8_t *)s, 22,1000);  
}

void usart_init()
{
  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  HAL_UART_Receive_IT(&huart2,(uint8_t *)aRxBuffer,RXBUFFERSIZE);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  
  uint32_t isrflags   = READ_REG(huart->Instance->SR);//�ֲ����н��������Ҫ�ȶ�SR
  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET)
  {
    READ_REG(huart->Instance->DR);//PE���־���ڶ�����DR
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);//���־
  }
  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET)
  {
    READ_REG(huart->Instance->DR);//FE���־���ڶ�����DR
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
  }
  
  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET)
  {
    READ_REG(huart->Instance->DR);//NE���־���ڶ�����DR
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);
  }        
  
  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET)
  {
    READ_REG(huart->Instance->CR1);//ORE���־���ڶ�����CR
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);
  }
  
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
  if(huart->Instance==USART2){ 
    if((USART_RX_STA&0x8000)==0)//USART_RX_STA��bit15Ϊ1����2^15=32768,ʮ�����Ʊ�ʾΪ0x8000��λ��Ϊ0˵����ʮ��λ��Ϊ1������δ���
    {
      if((USART_RX_STA&0x4000)!=0)//USART_RX_STA��bit14Ϊ1����2^14=16384,ʮ�����Ʊ�ʾΪ0X4000��λ�벻Ϊ0˵����ʮ��λΪ1�����յ�0x0d
      {
        if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//���յ���0x0d���ǻ���������0x0a���򲻷������ǵ�Э�飬���ܴ������¿�ʼ
        else USART_RX_STA|=0x8000;//������ճɹ���USART_RX_STA��λ��0x8000�������ĵ�15λ��1��ʾ�������
      }
      else// δ���յ�0x0d
      {
        if(aRxBuffer[0]==0x0d)//�������Ѿ���0x0d�Ļ�
        {
          USART_RX_STA|=0x4000;//��USART_RX_STA��14λ��1��ʾ���յ�0x0d
          USART_RX_BUF[USART_RX_STA&0x3fff]=aRxBuffer[0];
        }
        else//���������������0x0d
        {
          USART_RX_BUF[USART_RX_STA&0x3fff]=aRxBuffer[0];//�洢���������ΪUSART_RX_STA��0~13λ������ȡ�����Ǿ�λ��001111111111��Ȼ��ѻ�������ֵ��ֵ���洢����
          USART_RX_STA++;//�洢һ�α�־��1�����ں�����������ַ�����
          if(USART_RX_STA>(USART_REC_LEN-1))//�궨�������󳤶�USART_REC_LEN�����յ��ַ����ȹ������򱨴����¿�ʼ����
            USART_RX_STA=0;//���¿�ʼ����
        }       
      }                         
    }
  }
  HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);  
}

void usart_exc()
{
  int cmd_argc,len;
  int erro_n;
  if(USART_RX_STA&0x8000){//����Ƿ�������  //������һ��ָ��
    len=USART_RX_STA&0x3fff;//ȡ�����յĳ���
    if(len == 0){
      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
      USART_RX_STA=0;
      return;
    }
    erro_n = cmd_parse(USART_RX_BUF,&cmd_argc,cmd_argv);  //��������
    if(erro_n < 0){
      //��ӡ����ִ�д�����Ϣ
      if(erro_n == -3){
        len = 0;
        //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
        HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
        USART_RX_STA=0;
        return;
      }else if(erro_n == -2){
        uprintf("����������ȹ���\r\n");
        //USART_SendString(CMD_USARTx,"msg: ����������ȹ���\n");
      }else if(erro_n == -1){
        uprintf("�����������\r\n");
        //USART_SendString(CMD_USARTx,"msg: �����������\n");
      }
      len = 0;
      //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
      USART_RX_STA=0;
      return;
    }
    erro_n = cmd_exec(cmd_argc,cmd_argv);   //ִ������
    if(erro_n < 0){
      //��ӡ����ִ�д�����Ϣ
      if(erro_n == -2){
        uprintf("δ�ҵ�����%s\r\n",cmd_argv[0]);
        //USART_SendString(CMD_USARTx,"msg: δ�ҵ�����:%s\r\n",cmd_argv[0]);
      }
      len = 0;
      //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
      USART_RX_STA=0;
      return;
    }
    len = 0;
    //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
    USART_RX_STA=0;
  }
}
/* USER CODE END 1 */

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
