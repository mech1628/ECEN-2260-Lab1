/*
 * ApplicationCode.c
 *
 *  Created on: Aug 27, 2024
 *      Author: Owner
 */
#include "ApplicationCode.h" //do I even need to include this here?
#define GPIOG_RCC_ENABLE_ADDRESS 0x40023830                         //direct address of GPIOG register, plus offset, both in hex: add normally
#define GPIOG_AHB1ENR_BIT_OFFSET 6                                  //bit offset is in decimal (the place in the address that needs updated)
#define GPIOG_ODR_LED_BIT_OFFSET 14
#define GPIOG_MODER_ENABLE_ADDRESS 0x40021800//GPIOG MODER direct address
#define GPIOG_LED_BIT_OFFSET 28 //GPIOG_MODER_OFFSET VALUE
#define GPIOG_ODR_ENABLE_ADDRESS 0x40021814
#define LengthOfName 7                                             //this entire list of defines are known as macros, like global variables

void AppDelay( uint32_t Delay){                                    //defining a variable of uint32_t type, named Delay
	char NameArray[LengthOfName];				   //deifning character array, but could also hold one bit numbers
	char DestinationArray[LengthOfName];

	for( uint32_t i = 0; i < Delay;i++){  			  //( 32 bit integer i, =0, loop until i< Delay value(defined in main.c), increment i by 1)
		for( uint32_t j = 0; j < LengthOfName; j++){	  
			NameArray[j] = DestinationArray[j];	  //input whatever is at the j position of one array, into the j position of other array
		}
	}
}

void EnablePeripheralsAndClocks(){
	uint32_t * RCCclkPtr = (uint32_t*) GPIOG_RCC_ENABLE_ADDRESS;    //pointer of 32bit-int type, called RCCclkPTR which equals the macro at the top
	*RCCclkPtr |= (0x1 << GPIOG_AHB1ENR_BIT_OFFSET);                //"or" bits to clear them, 0x1= 0b0001, we input 0001 into the value *RCCclkPTR, offset by value of 6 
									//First thing is first!! SET THE CLOCK AND ALL ITS RELATED CONFIGURATIONS FIRST!!!!! everything runs on the clock!!
	uint32_t * MODERPtr = (uint32_t*) GPIOG_MODER_ENABLE_ADDRESS;  
	*MODERPtr &= ~(0x3 << GPIOG_LED_BIT_OFFSET);			//clearing bits: first input 0x3, which = 0b0011, into the *moderptr, then not it to get just zeroes in the place of interest
	*MODERPtr |= (0x1 << GPIOG_LED_BIT_OFFSET);			//then "and" with the *ptr value which will return 0's for all values not of interest, then "or" to set bit values


}

void TurnOnRedLed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;  	//ORDpts is pointuing to the value at the enable adresss
	*ODRPtr |= (0x1 << GPIOG_ODR_LED_BIT_OFFSET); 			//setting the bits to 01 at a specific place, that live at the enable address,
}

void TurnOffRedLed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;
	*ODRPtr &= ~(0x1 << GPIOG_ODR_LED_BIT_OFFSET);			//clearing bits
}

void ToggleRed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;	//adress of status of led
	int LED_STATE = (*ODRPtr & (0x1<<GPIOG_ODR_LED_BIT_OFFSET));	//setting it to a vale >0

	if (LED_STATE >= 1) {
		TurnOffRedLed();

	}
	else {
		TurnOnRedLed();

	}
}
