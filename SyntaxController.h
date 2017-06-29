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

class SyntaxController
{
public:
  char *pFileType;
  char **ppFileAccordance;
  char **ppKeywords; // example: types, operator etc.
  char *singlelineCommentStart; // '//' - singleline comment
  char *multilineCommentStart; // '/*' - multiline comment start
  char *multilineCommentEnd; // '*/' - multiline comment end
  int flags;
};

SyntaxController snx[] = {
                          {"c", pFileExtension, pKeywords,
                            "//", "/*", "*/",
                            CLR_COLORFUL_NUMBERS | CLR_COLORFUL_STRINGS},
                         };
