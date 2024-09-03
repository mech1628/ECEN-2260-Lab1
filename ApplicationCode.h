/*
 * ApplicationCode.h
 *
 *  Created on: Aug 27, 2024
 *      Author: Owner
 */


#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_
#include <stdint.h>
void AppDelay(uint32_t Delay);
void EnablePeripheralsAndClocks();
void TurnOnRedLed();
void TurnOffRedLed();
void ToggleRed(); //this could possibly a boolean, TorF, 1or0

#endif /* APPLICATIONCODE_H_ */

