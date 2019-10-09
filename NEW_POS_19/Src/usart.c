/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

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
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
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

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
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

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
//char uart_buffer[100 + 1];
//void uprintf(char *fmt, ...)
//{
//  int size;
//  
//  va_list arg_ptr;
//  
//  va_start(arg_ptr, fmt);  
//  
//  size=vsnprintf(uart_buffer, 100 + 1, fmt, arg_ptr);
//  va_end(arg_ptr);
//  HAL_UART_Transmit(&huart2,(uint8_t *)uart_buffer,size,1000);
//}
//
//char s[22]={'b','y',16,6};
//void send_wave(float arg1,float arg2,float arg3,float arg4){
//  
//  s[2]=16;  //length
//  s[3]=6;   //pe
//  s[20]='\r';
//  s[21]='\n';
//  memcpy(s+4,&arg1,sizeof(arg1));
//  memcpy(s+8,&arg2,sizeof(arg1));
//  memcpy(s+12,&arg3,sizeof(arg1));
//  memcpy(s+16,&arg4,sizeof(arg1));
//  HAL_UART_Transmit(&huart2,(uint8_t *)s, 22,1000);  
//}
//
//void usart_init()
//{
//  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
//  HAL_NVIC_EnableIRQ(USART2_IRQn);
//  HAL_UART_Receive_IT(&huart2,(uint8_t *)aRxBuffer,RXBUFFERSIZE);
//}
//
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
//{
//  
//  uint32_t isrflags   = READ_REG(huart->Instance->SR);//�ֲ����н��������Ҫ�ȶ�SR
//  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET)
//  {
//    READ_REG(huart->Instance->DR);//PE���־���ڶ�����DR
//    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_PE);//���־
//  }
//  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET)
//  {
//    READ_REG(huart->Instance->DR);//FE���־���ڶ�����DR
//    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
//  }
//  
//  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET)
//  {
//    READ_REG(huart->Instance->DR);//NE���־���ڶ�����DR
//    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);
//  }        
//  
//  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET)
//  {
//    READ_REG(huart->Instance->CR1);//ORE���־���ڶ�����CR
//    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE);
//  }
//  
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{ 
//  if(huart->Instance==USART2){ 
//    if((USART_RX_STA&0x8000)==0)//USART_RX_STA��bit15Ϊ1����2^15=32768,ʮ�����Ʊ�ʾΪ0x8000��λ��Ϊ0˵����ʮ��λ��Ϊ1������δ���
//    {
//      if((USART_RX_STA&0x4000)!=0)//USART_RX_STA��bit14Ϊ1����2^14=16384,ʮ�����Ʊ�ʾΪ0X4000��λ�벻Ϊ0˵����ʮ��λΪ1�����յ�0x0d
//      {
//        if(aRxBuffer[0]!=0x0a)USART_RX_STA=0;//���յ���0x0d���ǻ���������0x0a���򲻷������ǵ�Э�飬���ܴ������¿�ʼ
//        else USART_RX_STA|=0x8000;//������ճɹ���USART_RX_STA��λ��0x8000�������ĵ�15λ��1��ʾ�������
//      }
//      else// δ���յ�0x0d
//      {
//        if(aRxBuffer[0]==0x0d)//�������Ѿ���0x0d�Ļ�
//        {
//          USART_RX_STA|=0x4000;//��USART_RX_STA��14λ��1��ʾ���յ�0x0d
//          USART_RX_BUF[USART_RX_STA&0x3fff]=aRxBuffer[0];
//        }
//        else//���������������0x0d
//        {
//          USART_RX_BUF[USART_RX_STA&0x3fff]=aRxBuffer[0];//�洢���������ΪUSART_RX_STA��0~13λ������ȡ�����Ǿ�λ��001111111111��Ȼ��ѻ�������ֵ��ֵ���洢����
//          USART_RX_STA++;//�洢һ�α�־��1�����ں�����������ַ�����
//          if(USART_RX_STA>(USART_REC_LEN-1))//�궨�������󳤶�USART_REC_LEN�����յ��ַ����ȹ������򱨴����¿�ʼ����
//            USART_RX_STA=0;//���¿�ʼ����
//        }       
//      }                         
//    }
//  }
//  HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);  
//}
//
//void usart_exc()
//{
//  int cmd_argc,len;
//  int erro_n;
//  if(USART_RX_STA&0x8000){//����Ƿ�������  //������һ��ָ��
//    len=USART_RX_STA&0x3fff;//ȡ�����յĳ���
//    if(len == 0){
//      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
//      USART_RX_STA=0;
//      return;
//    }
//    erro_n = cmd_parse(USART_RX_BUF,&cmd_argc,cmd_argv);  //��������
//    if(erro_n < 0){
//      //��ӡ����ִ�д�����Ϣ
//      if(erro_n == -3){
//        len = 0;
//        //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
//        HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
//        USART_RX_STA=0;
//        return;
//      }else if(erro_n == -2){
//        uprintf("����������ȹ���\r\n");
//        //USART_SendString(CMD_USARTx,"msg: ����������ȹ���\n");
//      }else if(erro_n == -1){
//        uprintf("�����������\r\n");
//        //USART_SendString(CMD_USARTx,"msg: �����������\n");
//      }
//      len = 0;
//      //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
//      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
//      USART_RX_STA=0;
//      return;
//    }
//    erro_n = cmd_exec(cmd_argc,cmd_argv);   //ִ������
//    if(erro_n < 0){
//      //��ӡ����ִ�д�����Ϣ
//      if(erro_n == -2){
//        uprintf("δ�ҵ�����%s\r\n",cmd_argv[0]);
//        //USART_SendString(CMD_USARTx,"msg: δ�ҵ�����:%s\r\n",cmd_argv[0]);
//      }
//      len = 0;
//      //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
//      HAL_UART_Receive_IT(&huart2,(uint8_t *)&aRxBuffer,RXBUFFERSIZE);
//      USART_RX_STA=0;
//      return;
//    }
//    len = 0;
//    //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
//    USART_RX_STA=0;
//  }
//}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
