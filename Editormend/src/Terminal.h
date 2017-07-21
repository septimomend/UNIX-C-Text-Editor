// Terminal.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   30.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "AllControllers.h"

class Terminal
{
public:
  Terminal(); // cstr

  void emergencyDestruction(const char* str);   // when something wrong
  void rowModeOn(); //
  void rowModeOff();

  int whatKey();                                // defines key pressing
  int getCursorPosition(int *row, int *column); // returns cursor position
  int getWindowSize(int *row, int *column);     // returns size of window

  AllControllers* getAllControllerObj() const;

private:
  AllControllers all;
  struct termios* termObj;
  ConfigurationController* configObj;
};
