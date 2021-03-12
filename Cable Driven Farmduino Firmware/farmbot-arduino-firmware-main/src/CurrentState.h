/*
 * CurrentState.h
 *
 *  Created on: 15 maj 2014
 *      Author: MattLech
 */

#ifndef CURRENTSTATE_H_
#define CURRENTSTATE_H_
#include "Arduino.h"
#include "pins.h"

enum ErrorListEnum
{
  ERR_NO_ERROR = 0,
  ERR_EMERGENCY_STOP = 1,
  ERR_TIMEOUT = 2,
  ERR_STALL_DETECTED = 3,
  ERR_CALIBRATION_ERROR = 4,

  ERR_INVALID_COMMAND = 14,
  ERR_PARAMS_NOT_OK = 15,

  ERR_STALL_DETECTED_X = 31,
  ERR_STALL_DETECTED_E = 34,
  ERR_STALL_DETECTED_Y = 32,
  ERR_STALL_DETECTED_Z = 33,
};

class CurrentState
{
public:
  static CurrentState *getInstance();

  long getX();
  long getE();
  long getY();
  long getZ();
  long *getPoint();
  void setX(long);
  void setE(long);
  void setY(long);
  void setZ(long);

  long getHomeMissedStepsX();
  long getHomeMissedStepsE();
  long getHomeMissedStepsY();
  long getHomeMissedStepsZ();
  long getHomeMissedStepsXscaled();
  long getHomeMissedStepsEscaled();
  long getHomeMissedStepsYscaled();
  long getHomeMissedStepsZscaled();
  void setHomeMissedStepsX(long);
  void setHomeMissedStepsE(long);
  void setHomeMissedStepsY(long);
  void setHomeMissedStepsZ(long);


  int getLastError();
  void setLastError(int error);

  void setEndStopState(unsigned int, unsigned int, bool);
  void printPosition();
  String getPosition();
  void storeEndStops();
  void printEndStops();
  void print();
  void printBool(bool);

  void setQ(long);
  void resetQ();
  void printQAndNewLine();
  String getQAndNewLine();

  void setEmergencyStop();
  void resetEmergencyStop();
  bool isEmergencyStop();

  void setStepsPerMm(long stepsX, long stepsE, long stepsY, long stepsZ);
  long getStepsPerMmX();
  long getStepsPerMmE();
  long getStepsPerMmY();
  long getStepsPerMmZ();


private:
  CurrentState();
  CurrentState(CurrentState const &);
  void operator=(CurrentState const &);

  long stepsPerMmX = 1;
  long stepsPerMmE = 1;
  long stepsPerMmY = 1;
  long stepsPerMmZ = 1;

  int errorCode = 0;

  long x = 0;
  long e = 0;
  long y = 0;
  long z = 0;
  unsigned int speed = 0;
  bool endStopState[4][2]; //may be wrong changed from 3 to 4
  long Q = 0;
  int lastError = 0;

  long homeMissedStepX = 0;
  long homeMissedStepE = 0;
  long homeMissedStepY = 0;
  long homeMissedStepZ = 0;


  bool emergencyStop = false;
};

#endif /* CURRENTSTATE_H_ */
