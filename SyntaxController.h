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
  char **ppKeywords; // example: types, operator etc.
  char *singlelineCommentStart; // '//' - singleline comment
  char *multilineCommentStart; // '/*' - multiline comment start
  char *multilineCommentEnd; // '*/' - multiline comment end
  int flags;

  // TODO: add some functions
};

SyntaxController snx[] = {
                          {"c", pFileExtension, pKeywords,
                            "//", "/*", "*/",
                            CLR_COLORFUL_NUMBERS | CLR_COLORFUL_STRINGS},
                         };

#define _SNX_ (sizeof(snx) / sizeof(snx[0]))
