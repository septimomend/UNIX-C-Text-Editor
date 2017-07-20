// RowController.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   29.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"

class RowController
{
protected:
  int index;
  int size;
  int sizeRow;
  char *pLetter;
  char *pVisualize; // ie render
  unsigned char *pClr;
  int commentClr;
};
