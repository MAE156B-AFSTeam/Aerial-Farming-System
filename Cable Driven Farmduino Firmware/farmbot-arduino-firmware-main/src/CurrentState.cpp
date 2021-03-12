/*
 * CurrentState.cpp
 *
 *  Created on: 15 maj 2014
 *      Author: MattLech
 */

#include "CurrentState.h"

static CurrentState *instance;

CurrentState *CurrentState::getInstance()
{
  if (!instance)
  {
    instance = new CurrentState();
  };
  return instance;
};

CurrentState::CurrentState()
{
  x = 0;
  e = 0;
  y = 0;
  z = 0;

  homeMissedStepX = 0;
  homeMissedStepE = 0;
  homeMissedStepY = 0;
  homeMissedStepZ = 0;

  speed = 0;
  Q = 0;
  lastError = 0;
}

long CurrentState::getX()
{
  return x;
}

long CurrentState::getE()
{
  return e;
}

long CurrentState::getY()
{
  return y;
}

long CurrentState::getZ()
{
  return z;
}

long *CurrentState::getPoint()
{
  static long currentPoint[4] = {x, e, y, z};
  return currentPoint;
}

void CurrentState::setX(long newX)
{
  x = newX;
}

void CurrentState::setE(long newE)
{
  e = newE;
}

void CurrentState::setY(long newY)
{
  y = newY;
}

void CurrentState::setZ(long newZ)
{
  z = newZ;
}

long CurrentState::getHomeMissedStepsX()
{
  return homeMissedStepX;
}

long CurrentState::getHomeMissedStepsXscaled()
{
  return homeMissedStepX / stepsPerMmX;
}

long CurrentState::getHomeMissedStepsE()
{
  return homeMissedStepE;
}

long CurrentState::getHomeMissedStepsEscaled()
{
  return homeMissedStepE / stepsPerMmE;
}

long CurrentState::getHomeMissedStepsY()
{
  return homeMissedStepY;
}

long CurrentState::getHomeMissedStepsYscaled()
{
  return homeMissedStepY / stepsPerMmY;
}

long CurrentState::getHomeMissedStepsZ()
{
  return homeMissedStepZ;
}

long CurrentState::getHomeMissedStepsZscaled()
{
  return homeMissedStepZ / stepsPerMmZ;
}

void CurrentState::setHomeMissedStepsX(long newX)
{
  homeMissedStepX = newX;
}

void CurrentState::setHomeMissedStepsE(long newE)
{
  homeMissedStepE = newE;
}

void CurrentState::setHomeMissedStepsY(long newY)
{
  homeMissedStepY = newY;
}

void CurrentState::setHomeMissedStepsZ(long newZ)
{
  homeMissedStepZ = newZ;
}




int CurrentState::getLastError()
{
  return lastError;
}

void CurrentState::setLastError(int error)
{
  lastError = error;
}

void CurrentState::setEndStopState(unsigned int axis, unsigned int position, bool state)
{
  endStopState[axis][position] = state;
}

void CurrentState::setStepsPerMm(long stepsX, long stepsE, long stepsY, long stepsZ)
{
  stepsPerMmX = stepsX;
  stepsPerMmE = stepsE;
  stepsPerMmY = stepsY;
  stepsPerMmZ = stepsZ;
}

long CurrentState::getStepsPerMmX()
{
  return stepsPerMmX;
}

long CurrentState::getStepsPerMmE()
{
  return stepsPerMmE;
}

long CurrentState::getStepsPerMmY()
{
  return stepsPerMmY;
}

long CurrentState::getStepsPerMmZ()
{
  return stepsPerMmZ;
}

void CurrentState::storeEndStops()
{
  CurrentState::getInstance()->setEndStopState(0, 0, digitalRead(X_MIN_PIN));
  CurrentState::getInstance()->setEndStopState(0, 1, digitalRead(X_MAX_PIN));
  CurrentState::getInstance()->setEndStopState(1, 0, digitalRead(X_MIN_PIN));
  CurrentState::getInstance()->setEndStopState(1, 1, digitalRead(X_MAX_PIN));
  CurrentState::getInstance()->setEndStopState(2, 0, digitalRead(Y_MIN_PIN));
  CurrentState::getInstance()->setEndStopState(2, 1, digitalRead(Y_MAX_PIN));
  CurrentState::getInstance()->setEndStopState(3, 0, digitalRead(Z_MIN_PIN));
  CurrentState::getInstance()->setEndStopState(3, 1, digitalRead(Z_MAX_PIN));
}

void CurrentState::printPosition()
{

  if (stepsPerMmX <= 0) { stepsPerMmX = 1; }
  if (stepsPerMmE <= 0) { stepsPerMmE = 1; }
  if (stepsPerMmY <= 0) { stepsPerMmY = 1; }
  if (stepsPerMmZ <= 0) { stepsPerMmZ = 1; }

  Serial.print("R82");
  Serial.print(" X");
  Serial.print((float)x / (float)stepsPerMmX);
  Serial.print(" E");
  Serial.print((float)e / (float)stepsPerMmE);
  Serial.print(" Y");
  Serial.print((float)y / (float)stepsPerMmY );
  Serial.print(" Z");
  Serial.print((float)z / (float)stepsPerMmZ * 1.0);
  printQAndNewLine();
}

String CurrentState::getPosition()
{

  if (stepsPerMmX <= 0) { stepsPerMmX = 1; }
  if (stepsPerMmE <= 0) { stepsPerMmE = 1; }
  if (stepsPerMmY <= 0) { stepsPerMmY = 1; }
  if (stepsPerMmZ <= 0) { stepsPerMmZ = 1; }

  String output = "";

  output += "R82";
  output += " X";
  output += (float)x / (float)stepsPerMmX * 1.0;
  output += " E";
  output += (float)e / (float)stepsPerMmE * 1.0;
  output += " Y";
  output += (float)y / (float)stepsPerMmY * 1.0;
  output += " Z";
  output += (float)z / (float)stepsPerMmZ * 1.0;

  return output;
}

void CurrentState::printBool(bool value)
{
  if (value)
  {
    Serial.print("1");
  }
  else
  {
    Serial.print("0");
  }
}

void CurrentState::printEndStops()
{
  Serial.print("R81");
  Serial.print(" XA");
  printBool(endStopState[0][0]);
  Serial.print(" XB");
  printBool(endStopState[0][1]);
  Serial.print(" EA");
  printBool(endStopState[1][0]);
  Serial.print(" EB");
  printBool(endStopState[1][1]);
  Serial.print(" YA");
  printBool(endStopState[2][0]);
  Serial.print(" YB");
  printBool(endStopState[2][1]);
  Serial.print(" ZA");
  printBool(endStopState[3][0]);
  Serial.print(" ZB");
  printBool(endStopState[3][1]);
  //Serial.print("\r\n");
  printQAndNewLine();
}

void CurrentState::print()
{
  printPosition();
  printEndStops();
}

void CurrentState::setQ(long q)
{
  Q = q;
}

void CurrentState::resetQ()
{
  Q = 0;
}

void CurrentState::printQAndNewLine()
{
  Serial.print(" Q");
  Serial.print(Q);
  Serial.print("\r\n");
}

String CurrentState::getQAndNewLine()
{
  String output = "";

  output += " Q";
  output += Q;
  output += "\r\n";

  return output;
}

void CurrentState::setEmergencyStop()
{
  emergencyStop = true;
}

void CurrentState::resetEmergencyStop()
{
  emergencyStop = false;
}

bool CurrentState::isEmergencyStop()
{
  return emergencyStop;
}
