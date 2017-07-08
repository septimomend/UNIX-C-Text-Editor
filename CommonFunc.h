// CommonFunc.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 30.06.2017
 *
 */
#pragma once
#include "stdafx.h"

class Common : public AllControllers
{
public:
  Common(); // cstr
  void statusMsg(const char *fmt, ...);
  void updateScreen();
  char *callPrompt(char *prompt, void (*callback)(char *, int));
};
