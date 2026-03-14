/*pwm_write.c*/
#include "debug.h"


void PWM_init(void){
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM1, ENABLE);

    /* PC3 = TIM1_CH3 PWM (TIM1 PWM needs AF_PP) */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Timer: 48MHz/24=2MHz, ARR=999 ¡ú ~2kHz PWM */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 24 - 1;
    TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    /* PWM CH3 on PC3 */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;  // Start 50%
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);

    /* CRITICAL for duty updates */
    TIM_OC3PreloadConfig(TIM1, DISABLE);  // Immediate update (not preload)
    TIM_ARRPreloadConfig(TIM1, DISABLE);  // Shadow not needed for simple PWM

    TIM_CtrlPWMOutputs(TIM1, ENABLE);  // TIM1 BDTR MOE enable
    TIM_Cmd(TIM1, ENABLE);

    


}