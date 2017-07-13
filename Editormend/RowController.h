// RowController.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 29.06.2017
 *
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
