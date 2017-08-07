// CommonFunc.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   30.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "AllControllers.h"
#include "AdditionalBuffer.h"
#include "Terminal.h"

class Common : public AllControllers
{
public:
  Common();                    // default cstr
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
   * editor operations
   */
  void openFile(char *filename);
  void save();
  void find();

private:
  ConfigurationController* m_pCnfg;
  Adbfr m_abfr;
  Terminal tml;
  AllControllers* m_All;
};
