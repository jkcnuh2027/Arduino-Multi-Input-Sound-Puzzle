//Han 11/21
//Adding extra features to integrate.c
//The buzzer now will continuously buzzing until the user enter the correct pattern (This makes the game more intense psychologically)
//To hear the pattern again, user need to press the reset(black button)
#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"
int note[5]={0,1,0,1,0}; //The desired pattern played by buzzer
int input[5]={2,2,2,2,2}; //The input array
int i=0;
int gameWon = 0;

int buttonStatePrevious = 1;                      // previousstate of the switch

unsigned long minButtonLongPressDuration = 800;    // Time we wait before we see the press as a long press
unsigned long buttonLongPressMillis;                // Time in ms when we the button was pressed
bool buttonStateLongPress = false;                  // True if it is a long press

const int intervalButton = 50;                      // Time between two readings of the button state
unsigned long previousButtonMillis;                 // Timestamp of the latest reading

unsigned long buttonPressDuration;                  // Time the button is pressed in ms



bool result=false;
//// GENERAL ////

unsigned long currentMillis;         
 // Variabele to store the number of milleseconds since the Arduino has started
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
     InitializePin(GPIOA,GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);
    
    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);
    
    
    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

    // Wait for the user to push the blue button, then blink the LED.

    // wait for button press (active low)

buzzer(); //USER MUST PRESS THE BUTTON AFTER THE BUZZ STOPS!!!!!!!!!!!!!!!
while(true){
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
check();    
currentMillis=HAL_GetTick();
readButtonState();

}   



    return 0;
}
void check(){
    InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); 
  
    if(input[0]==note[0]&&input[1]==note[1]&&input[2]==note[2]&&input[3]==note[3]&&input[4]==note[4]){
         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
         HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
         gameWon += 1;
    }
    else if (i == 5) { //To ensure that all 5 entries are inputted
        char buff[100];
        sprintf(buff, "Try again.\n");
        SerialPuts(buff);
        i = 0;
    }
    if (gameWon == 1){
         char buff[100];
         sprintf(buff, "Congratulations, You won the game!\n");
         SerialPuts(buff);
        gameWon += 1; //Works only once; sprintf in an if loop will print in milliseconds, so I made it stop after once
    }
    
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
      input[i]=1;
      i++;
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
      // Note: The video shows:
      //       if (!buttonStateLongPress && buttonPressDuration < minButtonLongPressDuration) {
      //       since buttonStateLongPress is set to FALSE on line 75, !buttonStateLongPress is always TRUE
      //       and can be removed.
      if (buttonPressDuration < minButtonLongPressDuration) {
          input[i]=0;
         i++;
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
