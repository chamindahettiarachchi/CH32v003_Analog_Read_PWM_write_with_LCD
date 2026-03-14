/*adc_read.c*/
#include "debug.h"

 void my_ADC_init(void){
        /* Enable clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);

    /* PD2 = analog input */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Reset ADC */
    ADC_DeInit(ADC1);

    /* ADC basic configuration */
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* Enable ADC */
    ADC_Cmd(ADC1, ENABLE);

    /* Calibrate ADC */
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));

 }

 uint16_t Read_ADC(void)
{
    /* PD2 = A3 -> ADC channel 3 */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_15Cycles);

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC1);
}