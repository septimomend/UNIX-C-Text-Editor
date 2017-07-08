// AdditionalBuffer.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 08.07.2017
 *
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
