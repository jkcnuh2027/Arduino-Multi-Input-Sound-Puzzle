// Sample code for ECE 198

// Written by Bernie Roehl, August 2021

// This file contains code for a number of different examples.
// Each one is surrounded by an #ifdef ... #endif block inside of main().

// To run a particular example, you should remove the comment (//) in
// front of exactly ONE of the following lines:
//Since we have a active buzzer, use HAL.delay
#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

int buzzer(void){
     InitializePin(GPIOA, GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    int between = 200;
    for(int i=0;i<3;i++) 
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
        HAL_Delay(200); //First note (short)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
        HAL_Delay(between); //pause
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
        HAL_Delay(700); //Second note (long)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
        HAL_Delay(between);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
        HAL_Delay(200); //Third note (short)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
        HAL_Delay(between);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
        HAL_Delay(1000); //Fourth note (long)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
        HAL_Delay(between);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
        HAL_Delay(200); //Fifth note (short)
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
        HAL_Delay(2000); //Pause before loop
    }                    //This is a buzzer function that allows the buzzer to sound, use HAL_delay to modify the length
}
int LED(void){
     InitializePin(GPIOA,GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    
while (true)
    {
        while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
            ;
        {

            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
            while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
                ;
            {

                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
                while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
                    ;
                {

                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
                    while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
                        ;
                    {

                        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
                    }
                }
            }
        }
    }
 
}
int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
buzzer();
LED();

    
    
   
   

    return 0;
}

// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
