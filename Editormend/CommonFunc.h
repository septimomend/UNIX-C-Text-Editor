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

private:
  ConfigurationController* m_cnfg;
  Adbfr m_abfr;
  Terminal tml;
};
