#include "stm8s.h"
#include "stm8s_exti.h"


void Delay(uint16_t nCount)
{
  while (nCount != 0)
  {   
    nCount--;
  }  
}


void ExTiKey_init()
{
  EXTI_DeInit();
  
  GPIO_Init(GPIOB, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);
  GPIO_Init(GPIOD, GPIO_PIN_3|GPIO_PIN_7, GPIO_MODE_IN_PU_IT);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  
 
  enableInterrupts();
  
}
void LedPort_init()
{
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_LOW_FAST);
}

void Timer4_init()
{
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 0xff);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);

}

void Uart1_Init()
{
  UART1_DeInit();
  
  UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, 
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
  
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  
  UART1_Cmd(ENABLE);
   
}


void Send_Dat(unsigned char dat)
{
   while(UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
   UART1_SendData8(dat);
}


void Send_Str(unsigned char* dat)
{
  
  while(*dat != '\0')
  {
    Send_Dat(*dat);
 
    dat++;
  
  }

}


void main(void)
{ 
  
  LedPort_init();
  ExTiKey_init();
  Timer4_init();
  
  while (1)
  {

  }
  
  
}



#ifdef USE_FULL_ASSERT

void assert_failed(u8* file, u32 line)
{ 
  while (1)
  {
  }
}
#endif