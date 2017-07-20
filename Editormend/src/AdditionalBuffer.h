// AdditionalBuffer.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   08.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "AllControllers.h"

class Adbfr
{
public:
  Adbfr(); // cstr

  char *bfr;
  int sizeBfr;

  void reallocateBfr(const char *content, int size);
  void freeBfr();
};
