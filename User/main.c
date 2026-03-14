/*main.c*/
#include "debug.h"
#include "st7567.h"
#include "adc_read.h"
#include "pwm_write.h"
#include "strings.h"
#include <stdio.h>

unsigned long  ADC = 0;
uint16_t v = 0;
char str[30];

int main(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
     SystemCoreClockUpdate();
     Delay_Init();


    my_ADC_init();
    PWM_init();
    

   lcd_init(); 
   Delay_Ms(200);

   lcd_clear();
  // lcd_string(0, 0, "read ADC");
   //lcd_string(0, 1, " with");
  // lcd_string(0, 2, "variable resistor");


while(1){
uint16_t adc_value = Read_ADC();
uint16_t pwm_value = ((uint32_t)adc_value * 999) / 1023;
unsigned long mv = ((unsigned long)adc_value * 3300) / 1023;   // use 5000 if VDD = 5V

sprintf(str, "ADC     = %4u   ", adc_value);
lcd_string(0, 0, str);

sprintf(str, "Voltage = %lu.%03luV   ", mv / 1000, mv % 1000);
lcd_string(0, 1, str);

sprintf(str, "PWM     = %4u   ", pwm_value);
lcd_string(0, 2, str);

TIM_SetCompare3(TIM1, pwm_value);
Delay_Ms(50);
  
}




}