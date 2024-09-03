/*
 * ApplicationCode.c
 *
 *  Created on: Aug 27, 2024
 *      Author: Owner
 */
#include "ApplicationCode.h" //do I even need to include this here?
#define GPIOG_RCC_ENABLE_ADDRESS 0x40023830
#define GPIOG_AHB1ENR_BIT_OFFSET 6
#define GPIOG_ODR_LED_BIT_OFFSET 14
#define GPIOG_MODER_ENABLE_ADDRESS 0x40021800//GPIOG MODER direct address
#define GPIOG_LED_BIT_OFFSET 28 //GPIOG_MODER_OFFSET VALUE
#define GPIOG_ODR_ENABLE_ADDRESS 0x40021814
#define LengthOfName 7

void AppDelay( uint32_t Delay){
	char NameArray[LengthOfName];
	char DestinationArray[LengthOfName];

	for( uint32_t i = 0; i < Delay;i++){
		for( uint32_t j = 0; j < LengthOfName; j++){
			NameArray[j] = DestinationArray[j];
		}
	}
}

void EnablePeripheralsAndClocks(){
	uint32_t * RCCclkPtr = (uint32_t*) GPIOG_RCC_ENABLE_ADDRESS;
	*RCCclkPtr |= (0x1 << GPIOG_AHB1ENR_BIT_OFFSET); //First thing is first!! SET THE CLOCK AND ALL ITS RELATED CONFIGURATIONS FIRST!!!!!

	uint32_t * MODERPtr = (uint32_t*) GPIOG_MODER_ENABLE_ADDRESS;

	*MODERPtr &= ~(0x3 << GPIOG_LED_BIT_OFFSET);
	*MODERPtr |= (0x1 << GPIOG_LED_BIT_OFFSET);


}

void TurnOnRedLed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;
	*ODRPtr |= (0x1 << GPIOG_ODR_LED_BIT_OFFSET);
}

void TurnOffRedLed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;
	*ODRPtr &= ~(0x1 << GPIOG_ODR_LED_BIT_OFFSET);
}

void ToggleRed(){
	uint32_t * ODRPtr = (uint32_t*) GPIOG_ODR_ENABLE_ADDRESS;
	int LED_STATE = (*ODRPtr & (0x1<<GPIOG_ODR_LED_BIT_OFFSET));

	if (LED_STATE >= 1) {
		TurnOffRedLed();

	}
	else {
		TurnOnRedLed();

	}
}
