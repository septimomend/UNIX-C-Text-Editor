// ConfigurationController.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   29.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "SyntaxController.h"

class ConfigurationController : public SyntaxController
{
public:
  ConfigurationController();
  struct termios getTermios() const;

  /*
   * row operations
   */
  void updateRow(RowController *row);
  void setRow(int num, char *str, size_t sz);
  void setRowChar(RowController *row, int to, int ch);

protected:
  int configX, configY;
  int rowX;
  int disableRow; // disable
  int disableClr; // row and colour
  int enableRow;  // and enable row
  int enableClr;  // and colour
  int rowCount;   // number of rows
  int smear;
  char *pFilename;
  char statusMessage[80];
  time_t statusMessageTime;

  RowController *pRowObj; // RowController's object
  SyntaxController *pSyntaxObj; // SyntaxController's object
  struct termios baseTermiosObj; // for working with terminal's i/o interface
};
