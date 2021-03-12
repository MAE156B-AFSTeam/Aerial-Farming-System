/*
 * G00Handler.cpp
 *
 *  Created on: 15 maj 2014
 *      Author: MattLech
 */

#include "G00Handler.h"
static G00Handler *instance;

const double POST_ONE_LOCATIONs[2] = { 0,0 };
const double POST_TWO_LOCATIONs[2] = { 0,1500 };
const double POST_THREE_LOCATIONs[2] = { 1500,1500 };
const double POST_FOUR_LOCATIONs[2] = { 1500,0 };
const double POST_HEIGHTs = 1500;

G00Handler *G00Handler::getInstance()
{
  if (!instance)
  {
    instance = new G00Handler();
  };
  return instance;
};

G00Handler::G00Handler()
{
}

int G00Handler::execute(Command *command)
{
  
 	Serial.print("G00 was here\r\n");

  	Serial.print("R99");
  	Serial.print(" X ");
  	Serial.print(command->getX());
  	Serial.print(" Y ");
  	Serial.print(command->getY());
  	Serial.print(" Z ");
  	Serial.print(command->getZ());
  	Serial.print(" A ");
  	Serial.print(command->getA());
  	Serial.print(" B ");
  	Serial.print(command->getB());
  	Serial.print(" C ");
  	Serial.print(command->getC());
  	Serial.print("\r\n");


  
    double length1 = round(sqrt(pow(abs(command->getX() - POST_ONE_LOCATIONs[0]), 2) + pow(abs(command->getY() - POST_ONE_LOCATIONs[1]), 2)));
    double length2 = round(sqrt(pow(abs(command->getX() - POST_TWO_LOCATIONs[0]), 2) + pow(abs(command->getY() - POST_TWO_LOCATIONs[1]), 2)));
    double length3 = round(sqrt(pow(abs(command->getX() - POST_THREE_LOCATIONs[0]), 2) + pow(abs(command->getY() - POST_THREE_LOCATIONs[1]), 2)));
    double length4 = round(sqrt(pow(abs(command->getX() - POST_FOUR_LOCATIONs[0]), 2) + pow(abs(command->getY() - POST_FOUR_LOCATIONs[1]), 2)));

    Serial.print("G00 length coords");
    Serial.print(" L1 ");
    Serial.print(length1);
    Serial.print(" L2 ");
    Serial.print(length2);
    Serial.print(" L3 ");
    Serial.print(length3);
    Serial.print(" L4 ");
    Serial.print(" L5 ");
    Serial.print(length4);
    Serial.print("\r\n");

  Movement::getInstance()->moveToCoords(
      length1, length2, length3, length4,
      command->getA(), command->getB(), command->getC(), command->getD(),
      false, false, false, false);

  if (LOGGING)
  {
    CurrentState::getInstance()->print();
  }
  return 0;
}
