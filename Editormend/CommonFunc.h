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
#include "AllControllers.h"
#include "AdditionalBuffer.h"
#include "Terminal.h"

class Common : public AllControllers
{
public:
  Common(AllControllers* all); // cstr

  /*
   * draws
   */
  void drawRows(Adbfr* abfr);
  void drawStatusBar(Adbfr* abfr);
  void drawMessageBar(Adbfr* abfr);

  /*
   * operations
   */
  void statusMsg(const char *fmt, ...);
  void updateScreen();
  char *callPrompt(char *prompt, void (*callback)(char *, int));
  void scrolling();
  void moveCursor(int key);
  void processingKeypress();

  /*
   * syntax operations
   */
  void updateSyntax(RowController *row);

  /*
   * row operations
   */
  void updateRow(RowController *row);
  void setRow(int num, char *str, size_t sz);
  void setRowChar(RowController *row, int to, int ch);

  /*
   * editor operations
   */
  void setChar(int ch);
  void setNewline();
  void deleteChar();
  void save();
  void find();

private:
  ConfigurationController* m_pCnfg;
  Adbfr m_abfr;
  Terminal tml;
};
