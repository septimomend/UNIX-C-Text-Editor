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

class Terminal
{
public:
  Terminal(); // cstr
  void emergencyDestruction(const char* str);
  void rowModeOn();
  void rowModeOff();

  // TODO: add more
};
