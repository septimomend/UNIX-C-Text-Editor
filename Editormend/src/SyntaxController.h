// SyntaxController.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   27.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "FileTypes.h"
#include "RowController.h"

class SyntaxController : public RowController
{
public:
  SyntaxController();

  /*
   * syntax operations
   */
  int isDelimiter(int key);
  void updateSyntax(RowController *row);
  int colorizeSyntax(int clr);

protected:
  char *pFileType;
  char **ppFileAccordance;
  char **ppKeywords;              // example: types, operator etc.
  char *pSinglelineCommentStart;  // '//' - singleline comment
  char *pMultilineCommentStart;   // '/*' - multiline comment start
  char *pMultilineCommentEnd;     // '*/' - multiline comment end
  int flags;
};
