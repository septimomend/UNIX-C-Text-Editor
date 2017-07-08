// AdditionalBuffer.cpp -- source file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * Date: 08.07.2017
 *
 */

#include "stdafx.h"
#include "AdditionalBuffer.h"

Adbfr::Adbfr() // cstr
{
}

void reallocateBfr(const char *content, int size)
{
  char *newPlace = realloc(this->bfr, this->sizeBfr + size); // reallocate memory

  if (newPlace == NULL)
    return;        // if reallocation is false
  memcpy(&newPlace[this->sizeBfr], content, size); // fill new allocated memory by content
  this->bfr = newPlace;
  this->sizeBfr += size;
}

void freeBfr()
{
  free(this->bfr); // free memory
}
