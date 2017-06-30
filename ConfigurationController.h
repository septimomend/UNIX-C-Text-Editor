// ConfigurationController.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 29.06.2017
 *
 */

#pragma once

#include "stdafx.h"
#include "SyntaxController.h"

class ConfigurationController : public SyntaxController
{
  int configX, configY;
  int rowX;
  int disableRow; // disable
  int disableClr; // row and colour
  int enableRow; // and enable row
  int enableClr; // and colour
  int rowCount; // number of rows
  int smear;
  char *pFilename;
  char statusMessage[80];
  time_t statusMessageTime;
  RowController *pRowObj; // RowController's object
  SyntaxController *pSyntaxObj; // SyntaxController's object
  struct termios baseTermiosObj; // for working with terminal's i/o interface
}
