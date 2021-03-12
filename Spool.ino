#include <TMC2130Stepper.h>
#include <TMC2130Stepper_REGDEFS.h>
#include <TMC2130Stepper_UTILITY.h>
#include <SPI.h>



#define X_CS 24
#define E_CS 29
#define Y_CS 28
#define Z_CS 23

#define X_EN 25
#define E_EN 14
#define Y_EN 31
#define Z_EN 34

#define X_DIR 27
#define E_DIR 30
#define Y_DIR 33
#define Z_DIR 36

#define X_STEP 26
#define E_STEP 15
#define Y_STEP 32
#define Z_STEP 35

unsigned long int curr_time = 0;

bool dir = true;


#include <TMC2130Stepper.h>
TMC2130Stepper TMC2130_X = TMC2130Stepper(X_EN, X_DIR, X_STEP, X_CS);
TMC2130Stepper TMC2130_E = TMC2130Stepper(E_EN, E_DIR, E_STEP, E_CS);
TMC2130Stepper TMC2130_Y = TMC2130Stepper(Y_EN, Y_DIR, Y_STEP, Y_CS);
TMC2130Stepper TMC2130_Z = TMC2130Stepper(Z_EN, Z_DIR, Z_STEP, Z_CS);

void setup() {
  Serial.begin(9600);
  TMC2130_X.begin(); 
  TMC2130_X.SilentStepStick2130(1000); 
  TMC2130_X.stealthChop(1); 

  TMC2130_E.begin(); 
  TMC2130_E.SilentStepStick2130(1000); 
  TMC2130_E.stealthChop(1); 

  TMC2130_Y.begin(); 
  TMC2130_Y.SilentStepStick2130(1000); 
  TMC2130_Y.stealthChop(1); 

  TMC2130_Z.begin(); 
  TMC2130_Z.SilentStepStick2130(1000); 
  TMC2130_Z.stealthChop(1); 

  digitalWrite(X_EN, LOW);
  digitalWrite(E_EN, LOW);
  digitalWrite(Y_EN, LOW);
  digitalWrite(Z_EN, LOW);
}

void loop() {
  curr_time = millis();
  if (curr_time <= 10000) {
    digitalWrite(X_STEP, HIGH); digitalWrite(X_DIR, HIGH);
    digitalWrite(E_STEP, HIGH); digitalWrite(E_DIR, LOW);
    digitalWrite(Y_STEP, HIGH); digitalWrite(Y_DIR, HIGH);
    digitalWrite(Z_STEP, HIGH); digitalWrite(Z_DIR, LOW);
    delayMicroseconds(10);
    Serial.print(millis());        
  } else {
    digitalWrite(X_STEP, LOW); digitalWrite(E_STEP, LOW); digitalWrite(Y_STEP, LOW); digitalWrite(Z_STEP, LOW);
    delayMicroseconds(10);
  }
}
