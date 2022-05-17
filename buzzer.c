//Han Dong buzzer
//Paste the following code to main.c, the PIN7(D11) is used here, connect it to positive, and negative to the ground
//#define BUZZER

#ifdef BUZZER
InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); 
int between=200;
while(true){
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
HAL_Delay(200); //First note (short)
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
HAL_Delay(between); //pause
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
HAL_Delay(700); //Second note (long)
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
HAL_Delay(between);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
HAL_Delay(200); //Third note (short)
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
HAL_Delay(between);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
HAL_Delay(1000); //Fourth note (long)
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
HAL_Delay(between);
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
HAL_Delay(200); //Fifth note (short)
HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
HAL_Delay(2000); //Pause before loop
} //This is a buzzer function that allows the buzzer to sound, use HAL_delay to modify the length

#endif