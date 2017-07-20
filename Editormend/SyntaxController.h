// SyntaxController.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 27.06.2017
 *
 */
#pragma once

#include "stdafx.h"
#include "FileTypes.h"
#include "RowController.h"

class SyntaxController : public RowController
{
protected:
  char *pFileType;
  char **ppFileAccordance;
  char **ppKeywords;              // example: types, operator etc.
  char *pSinglelineCommentStart;  // '//' - singleline comment
  char *pMultilineCommentStart;   // '/*' - multiline comment start
  char *pMultilineCommentEnd;     // '*/' - multiline comment end
  int flags;

  // TODO: add some functions
};
