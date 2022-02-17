#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay_1(__IO uint32_t nCount);

int main(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Initialize LED which connected to PA1 */
  // Enable PORTA Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //GPIO_SetBits(GPIOA, GPIO_Pin_1); // Set A1 to High level ("1")
  GPIO_ResetBits(GPIOA, GPIO_Pin_1); // Set A1 to Low level ("0")

  /* Initialize Button input PB9 */
  // Enable PORTB Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* Configure the GPIO_BUTTON pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	uint32_t var_delay = 3000;

  while (1) {
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) != 0) {
		delay_1(var_delay);
		GPIOA->ODR ^= GPIO_Pin_1;
		
		delay_1(var_delay);
		GPIOA->ODR ^= GPIO_Pin_1;
		}
		else{
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		}
	}
}
void delay_1(__IO uint32_t nCount){
  for(; nCount != 0; nCount--);
}
