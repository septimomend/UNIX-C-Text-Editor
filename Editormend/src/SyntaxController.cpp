// SyntaxController.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   21.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "SyntaxController.h"

using namespace std;

SyntaxController::SyntaxController()
{
}

int SyntaxController::isDelimiter(int key)
{
  // return value if this space OR this is end of file symbol
  // OR key is one of ,.()+-/*=~%<>[]; symbols
  //
  return isspace(key) || key == '\0' || strchr(",.()+-/*=~%<>[];", key) != NULL;
}

void SyntaxController::updateSyntax(RowController *row)
{
  row->pClr = realloc(row->pClr, row->sizeRow); // reallocate memory
  memset(row->pClr, CLR_NORMAL, row->sizeRow);    // fill memory of pClr by 0

  if (m_pCnfg->pSyntaxObj == NULL)
    return;

  char **ppKwds = pSyntaxObj->ppKeywords;

  char *pScs = m_pCnfg->pSyntaxObj->pSinglelineCommentStart;  // "//..." - single comment
  char *pMcs = m_pCnfg->pSyntaxObj->pMultilineCommentStart;   // "/*..." - start comment block
  char *pMce = m_pCnfg->pSyntaxObj->pMultilineCommentEnd;     // "...*/" - end comment block

  // size of comments
  //
  int szScs = pScs ? strlen(pScs) : 0;
  int szMcs = pMcs ? strlen(pMcs) : 0;
  int szMce = pMce ? strlen(pMce) : 0;

  int prevDelimiter = 1;
  int insideString = 0;
  int insideComment = (row->index > 0 && m_pCnfg->pRowObj[row->index - 1].commentClr);

  int i = 0;
  while (i < row->sizeRow)
  {
    char c = row->pVisualize[i];                                     // reflected (showned) symbols
    unsigned char prevClr = (i > 0) ? row->pClr[i - 1] : CLR_NORMAL; // get previous color

    // if comment is there and cursor is not inside it
    // set comment color
    //
    if (szScs && !insideString && !insideComment)
    {
      if (!strncmp(&row->pVisualize[i], pScs, szScs)) // compare szScs num of symbols of pScs with pVisualize array
      {
        // if they are equal, ie this is singleline comment - "//"
        // so if this is still comment row set comment color for symbol
        //
        memset(&row->pClr[i], CLR_COMMENT, row->sizeRow - i);
        break;
      }
    }

    if (szMcs && szMce && !insideString)
    {
      if (insideComment)
      {
        row->pClr[i] = CLR_MLCOMMENT;
        if (!strncmp(&row->pVisualize[i], pMce, szMce)) // if this is end of comment block "*/"
        {
          memset(&row->pClr[i], CLR_MLCOMMENT, szMce);  // set comment block colour
          i += szMce;                                   // and get out
          insideComment = 0;                            // from comment
          prevDelimiter = 1;
          continue;
        }
        else
        {
          i++;
          continue;
        }
      }
      else if (!strncmp(&row->pVisualize[i], pMcs, szMcs)) // if this is start of comment block "/*"
      {
        memset(&row->pClr[i], CLR_MLCOMMENT, szMcs);       // set colour for next symbol
        i += szMcs;                                        // increase comment size
        insideComment = 1;                                 // inside comment - OK
        continue;
      }
    }

    if (m_pCnfg->pSyntaxObj->flags & CLR_COLORFUL_STRINGS)
    {
      if (insideString)                         // if inside string, ie cout << "this srting..." << ...
      {
        row->pClr[i] = CLR_STRING;              // colour this string string
        if (c == '\\' && i + 1 < row->sizeRow)  // if this is system command (begins with "\")
        {
          row->pClr[i + 1] = CLR_STRING;        // set color after that symbol "\"
          i += 2;                               // and jump over
          continue;
        }
        if (c == insideString)
          insideString = 0;                     // end of string
        i++;
        prevDelimiter = 1;
        continue;
      }
      else
      {
        if (c == '"' || c == '\'')              // string begins
        {
          insideString = c;
          row->pClr[i] = CLR_STRING;            // set color for string
          i++;
          continue;
        }
      }
    }

    if (m_pCnfg->pSyntaxObj->flags & CLR_COLORFUL_NUMBERS)
    {
      // if this is number OR previous color was number color OR if
      // this is point "." and previous color was number color
      //
      if ((isdigit(c) && (prevDelimiter || prevClr == CLR_NUMBER)) || (c == '.' && prevClr == CLR_NUMBER))
      {
        row->pClr[i] = CLR_NUMBER;  // set color for this number
        i++;
        prevDelimiter = 0;
        continue;
      }
    }

    if (prevDelimiter)
    {
      int j;
      for (j = 0; ppKwds[j]; j++)
      {
        int ksz = strlen(ppKwds[j]);
        int kw2 = ppKwds[j][ksz - 1] == '|';  // if this is delimiter "|"
        if (kw2)
          ksz--;

        // if this is delimiter - .,; etc.
        //
        if (!strncmp(&row->pVisualize[i], ppKwds[j], ksz) && isDelimiter(row->pVisualize[i + ksz]))
        {
          memset(&row->pClr[i], kw2 ? CLR_KEYWORD2 : CLR_KEYWORD1, ksz); // set color for first or second keyword
          i += ksz;
          break;
        }
      }
      if (ppKwds[j] != NULL)
      {
        prevDelimiter = 0;
        continue;
      }
    }

    prevDelimiter = isDelimiter(c);
    i++;
  }

  // update syntax if color was changed
  //
  int changed = (row->commentClr != insideComment);
  row->commentClr = insideComment;
  if (changed && row->index + 1 < m_pCnfg->rowCount)
    updateSyntax(&m_pCnfg->pRowObj[row->index + 1]);
}

int SyntaxController::colorizeSyntax(int clr)
{
  // returning of matched color value
  //
  switch (clr)
  {
    case HL_COMMENT:
    case HL_MLCOMMENT:
      return 36;
    case HL_KEYWORD1:
      return 33;
    case HL_KEYWORD2:
      return 32;
    case HL_STRING:
      return 35;
    case HL_NUMBER:
      return 31;
    case HL_MATCH:
      return 34;

    default:
      return 37;
  }
}
