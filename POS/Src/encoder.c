#include "encoder.h"

int encoderX_dir=1;
int encoderY_dir=1;
void encoder_init()
{   
    HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
    
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);

    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
}

//int judge_dir()
