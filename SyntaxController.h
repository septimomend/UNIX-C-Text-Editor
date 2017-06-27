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

struct SyntaxController
{
  char *filetype;
  char **filematch;
  char **keywords;
  char *singleline_comment_start;
  char *multiline_comment_start;
  char *multiline_comment_end;
  int flags;
};

SyntaxController HLDB[] = {{"c", C_HL_extensions, C_HL_keywords, "//", "/*", "*/", HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS}, };
