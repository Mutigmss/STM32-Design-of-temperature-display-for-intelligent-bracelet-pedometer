#include "led.h"
#include "main.h"

//led 初始化
void LED_init(void)
{
	HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
}
/* led 点亮 */
void LED0_on(void)
{
	HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_RESET);

}
/* led 熄灭 */
void LED0_off(void)
{
	HAL_GPIO_WritePin(GPIOA, LED0_Pin, GPIO_PIN_SET);

}

void LED1_on(void)
{

	HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_RESET);
}
/* led 熄灭 */
void LED1_off(void)
{
	
	HAL_GPIO_WritePin(GPIOA, LED1_Pin, GPIO_PIN_SET);
}