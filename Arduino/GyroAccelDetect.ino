int i;

#include <I2Cdev.h>
#include <helper_3dmath.h>
#include <MPU9255.h>



MPU9255 accelgyro;

const int x = 0;
const int y = 1;
const int z = 2;



int16_t accel[3] = {0};
int accelMin[3] = {0};
int accelMax[3] = {0};

int16_t gyro[3] = {0};
int16_t gyroMin[3] = {0};
int16_t gyroMax[3] = {0};


#define LED_PIN 13
bool blinkState = false;


void resetGyroAccel(){
  // resets all values to default
  for(int i  = 0; i < 3; ++i){
    gyro[i] = 0;
    gyroMin[i] = 0;
    gyroMax[i] = 0;
    accel[i] = 0;
    accelMin[i] = 0;
    accelMax[i] = 0;
  }
}

void GyroAccelInit() {
  //Wire.begin();
  Wire.setModule(1);
  Wire.begin();
  
  accelgyro.initialize();

  pinMode(LED_PIN, OUTPUT);
}

void accelGyroMaxAverage(int numReadings){
  // takes the average reading for better results
  for(int i = 0; i < 3; ++i){
    accelMax[i] /= numReadings;
  }

  Serial.print("Accelerometer max average || ");
  Serial.print(accelMax[x]); Serial.print(" || ");
  Serial.print(accelMax[y]); Serial.print(" || ");
  Serial.println(accelMax[z]);
    
}

int16_t* accelGyroRead(){

  accelgyro.getAcceleration(&accel[x], &accel[y], &accel[z]); // Gives you rotation ???
  Serial.print("ACCEL/GYRO || ");
  Serial.print(map(accel[x], accelMin[x], accelMax[x], 0, 100)); Serial.print(" || ");
  Serial.print(map(accel[y], accelMin[y], accelMax[y], 0, 100)); Serial.print(" || ");
  Serial.print(map(accel[z], accelMin[z], accelMax[z], 0, 100)); Serial.println(" || ");
  //accelgyro.getRotation(&gx, &gy, &gz); //Gives you acceleration ??!

  return accel;

}
