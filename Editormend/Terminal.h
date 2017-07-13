// Terminal.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 30.06.2017
 *
 */

#pragma once

#include "stdafx.h"
#include "AllControllers.h"
#include "CommonFunc.h"

class Terminal
{
public:
  Terminal(); // cstr

  void emergencyDestruction(const char* str); // when something wrong
  void rowModeOn(); //
  void rowModeOff();

  int whatKey(); // defines key pressing
  int getCursorPosition(int *row, int *column); // returns cursor position
  int getWindowSize(int *row, int *column); // returns size of window

private:
  AllControllers all;
  truct termios* termObj;
  ConfigurationController* configObj;
  Common cmmn(all);
};
