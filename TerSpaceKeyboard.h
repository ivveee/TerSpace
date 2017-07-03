// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TerSpaceKeyboard_H_
#define _TerSpaceKeyboard_H_
#include "Arduino.h"
//add your includes for the project TerSpaceKeyboard here
#define NO_OF_MATRICES 5
#define NO_OF_KEYS 11
#define ASCII_FIRST_KEY 97
#define FIRST_MATRIX_PIN 3
#define FIRST_KEY_PIN 22

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
//char keys[NO_OF_MATRICES][NO_OF_KEYS];
bool pressed[NO_OF_MATRICES][NO_OF_KEYS];
int timeOfPressed[NO_OF_MATRICES][NO_OF_KEYS];


char keys[NO_OF_MATRICES][NO_OF_KEYS]={
		{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
/*1*/	{'f','<','d','u','l','t','~',';','p','b','q'},
		{'r','k','v','y','j','g','h','c','n','e','a'},
		{'-',' ',' ',' ',' ',' ',' ',' ',' ',' ',KEY_BACKSPACE},
		{'[','w','x','i','o',']','s','m','"','.','z'},
};
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project TerSpaceKeyboard here




//Do not add code below this line
#endif /* _TerSpaceKeyboard_H_ */
