// Do not remove the include below
#include "TerSpaceKeyboard.h"

#define NO_OF_MATRICES 5
#define NO_OF_KEYS 11
#define ASCII_FIRST_KEY 97
#define FIRST_MATRIX_PIN 3
#define FIRST_KEY_PIN 22



//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	//int curKey = ASCII_FIRST_KEY;
	for(int i=0;i<NO_OF_MATRICES;i++){
		pinMode(FIRST_MATRIX_PIN + i, OUTPUT);
		digitalWrite(FIRST_MATRIX_PIN + i,HIGH);

		for(int j=0;j<NO_OF_KEYS;j++){
			pinMode(FIRST_KEY_PIN + j + i*NO_OF_KEYS, INPUT_PULLUP);

			//keys[i][j] = ASCII_FIRST_KEY+ j + i*NO_OF_KEYS;
			pressed[i][j]=false;
			//curKey++;
		}
	}
	Keyboard.begin();
}

void loop()
{
	for(int i=0;i<NO_OF_MATRICES;i++){
		digitalWrite(FIRST_MATRIX_PIN + i,LOW);

		for(int j=0;j<NO_OF_KEYS;j++){
			int currentKeyPin = FIRST_KEY_PIN + j;
			int currentKeyValue = digitalRead(currentKeyPin);
			//Serial.println(currentKeyValue);
			if(currentKeyValue == LOW){
				//Serial.println("key");

				if(!pressed[i][j]){
					Serial.print("i:");
					Serial.print(i);
					Serial.print("j:");
					Serial.println(j);
					if(!(i==3 && j==1 && ((millis() - timeOfPressed[2][1]) < 300)))
						Keyboard.print(keys[i][j]);
					pressed[i][j] = true;
					timeOfPressed[i][j] = millis();
				}
				else if(keys[i][j]==KEY_BACKSPACE && (millis() - timeOfPressed[i][j]) > 600){
					timeOfPressed[i][j] = millis();
					pressed[i][j] = false;
				}

			}
			else
				if((millis() - timeOfPressed[i][j]) > 300)
					pressed[i][j] = false;
		}
		digitalWrite(FIRST_MATRIX_PIN + i,HIGH);

	}


//Add your repeated code here
}
