//Han Dong 11/20
//This is a function that differenctiates long and short press
//Credit to https://www.youtube.com/watch?v=TD7vjJy0w8U
#include <stdbool.h> 
#include <stdio.h>   
#include <stdlib.h>  

#include "ece198.h"
char note[5]={0,1,0,1,0};
char input[5]={};
int i;
int buttonStatePrevious = 1;                      // previousstate of the switch

unsigned long minButtonLongPressDuration = 1000;    // Time we wait before we see the press as a long press
unsigned long buttonLongPressMillis;                // Time in ms when we the button was pressed
bool buttonStateLongPress = false;                  // True if it is a long press

const int intervalButton = 50;                      // Time between two readings of the button state
unsigned long previousButtonMillis;                 // Timestamp of the latest reading

unsigned long buttonPressDuration;                  // Time the button is pressed in ms

//// GENERAL ////

unsigned long currentMillis;         
 // Variabele to store the number of milleseconds since the Arduino has started
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

    char buff[100];
      sprintf(buff,"Press button\n");
      SerialPuts(buff);
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)
   
while(true){
currentMillis=HAL_GetTick();
readButtonState();
}   
    


    return 0;
}
void readButtonState(){
if(currentMillis - previousButtonMillis > intervalButton) {
    
    // Read the digital value of the button (LOW/HIGH)
    int buttonState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);    

    // If the button has been pushed AND
    // If the button wasn't pressed before AND
    // IF there was not already a measurement running to determine how long the button has been pressed
    if (buttonState == 0 && buttonStatePrevious == 1 && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = 0;
      char buff[100];
      sprintf(buff,"button pressed\n");
      SerialPuts(buff);
    }

    // Calculate how long the button has been pressed
    buttonPressDuration = currentMillis - buttonLongPressMillis;

    // If the button is pressed AND
    // If there is no measurement running to determine how long the button is pressed AND
    // If the time the button has been pressed is larger or equal to the time needed for a long press
    if (buttonState == 0 && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      buttonStateLongPress = true;
     char buff[100];
      sprintf(buff,"Button long pressed\n");
      SerialPuts(buff);
    }
      
    // If the button is released AND
    // If the button was pressed before
    if (buttonState == 1 && buttonStatePrevious == 0) {
      buttonStatePrevious = 1;
      buttonStateLongPress = false;
     char buff[100];
      sprintf(buff,"Button released\n");
      SerialPuts(buff);

      // If there is no measurement running to determine how long the button was pressed AND
      // If the time the button has been pressed is smaller than the minimal time needed for a long press
      
      if (buttonPressDuration < minButtonLongPressDuration) {
         char buff[100];
      sprintf(buff,"Button pressed shortly\n");
      SerialPuts(buff);
      }
    }
    
    // store the current timestamp in previousButtonMillis
    previousButtonMillis = currentMillis;

  }
}
// This function is called by the HAL once every millisecond
void SysTick_Handler(void)
{
    HAL_IncTick(); // tell HAL that a new tick has happened
    // we can do other things in here too if we need to, but be careful
}
