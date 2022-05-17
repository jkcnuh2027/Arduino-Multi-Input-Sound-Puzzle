//Han LED function use as needed
//This is just for personal testing, Our project does not need this but the basic logic is here 
//#define BUTTON_BLINK
#ifdef BUTTON_BLINK
  
   InitializePin(GPIOA, GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0); 
   
  while(true){
   while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));{ // Read user click the button
   
       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1); //then the light goes on (This pretty much the only thing we need in the project)
       while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));{
   
       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
       while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));{
   
       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
         while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));{
   
       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
       
    
   }
   }
    
   }
   }
  }
  #endif
   