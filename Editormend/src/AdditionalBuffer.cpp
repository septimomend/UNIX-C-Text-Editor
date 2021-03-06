// AdditionalBuffer.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   08.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "AdditionalBuffer.h"

Adbfr::Adbfr() // cstr
{
}

void reallocateBfr(const char *content, int size)
{
  char *newPlace = realloc(this->bfr, this->sizeBfr + size);                    // reallocate memory

  if (newPlace == NULL)
    return;                                                                     // if reallocation is false
  memcpy(&newPlace[this->sizeBfr], content, size);                              // fill new allocated memory by content started from last storage data
  this->bfr = newPlace;                                                         // reinitialize buffer
  this->sizeBfr += size;                                                        // add added size
}

void freeBfr()
{
    free(this->bfr);                                                            // free memory
}
