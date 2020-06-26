#include <Wire.h>
#include <string.h>
#include <stdio.h>
#include <EEPROM.h>
#include <HW_EEPROM.h>

void WireRequestArray(int address, uint8_t* buffer, uint8_t amount);
void WireWriteRegister(int address, uint8_t reg, uint8_t value);
void WireWriteByte(int address, uint8_t value);

// flex resistor pins
const uint32_t flexCount = 5;
const uint32_t mapLow = 0;
extern const uint32_t mapHigh = 100;

// the A0 pin is shared with the potentiometer, turn potentiometer fully clockwise for best flex detection
// these pins have been tested to work the best with the orbit booster pack attached
const int flex[flexCount] = {A1,A2,A4,A5,A6};

// mapping values of minimum and maximum flex voltages
int flexMin[flexCount] = {0};
int flexMax[flexCount] = {0};
int flexLetter[26][flexCount] = {0};
int flexValue[flexCount]={0};


void resetFlex(){
  for(int i = 0; i < flexCount; ++i){
    flexMax[i] = 0;
    flexMin[i] = 0;
  }
}

void resetLetter(int letter){
  for(int i = 0; i < 26; ++i){
    flexLetter[letter][i] = 0;
  }
}

//void newLetter(){
//  for(int i = 0; i < 26; ++i){
//    for(int j = 0; j < flexCount; ++j){
//      flexLetter[i][j] = 0;
//    }
//  }
//}

int* flexRead(){
  // function returns a list of 5 flex values
  
  for(int i = 0; i < flexCount; ++i){
    flexValue[i] = map(analogRead(flex[i]), flexMin[i], flexMax[i], mapLow, mapHigh);
  }

  //  boosterPackUndoRead();
  
  // serial monitor print for debugging
  Serial.print("FLEX || ");
  Serial.print(flexValue[0]);
  Serial.print(" || ");
  Serial.print(flexValue[1]);
  Serial.print(" || ");
  Serial.print(flexValue[2]);
  Serial.print(" || ");
  Serial.print(flexValue[3]);
  Serial.print(" || ");
  Serial.print(flexValue[4]);
  Serial.println(" || ");

  return flexValue;
}

int flexLetterCalibration(int letter){
  
  // calibrates the value of all 5 flex resistors when hand is at said value
  
  int tempLetter[flexCount];
  for(int i = 0; i < flexCount; ++i){
    tempLetter[i] = analogRead(flex[i]);
    if(!tempLetter[i]) return 0;
    flexLetter[letter][i] += tempLetter[i] < 0 ? 0 : tempLetter[i] > 100 ? 100 : tempLetter[i];
  }
