// CommonFunc.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   02.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "CommonFunc.h"


Common::Common(AllControllers* all) : m_pCnfg(all->getConfigObj())
{
}

int Common::isDelimiter(int key)
{
  // return value if this space OR this is end of file symbol
  // OR key is one of ,.()+-/*=~%<>[]; symbols
  //
  return isspace(key) || key == '\0' || strchr(",.()+-/*=~%<>[];", key) != NULL;
}

void Common::updateSyntax(RowController *row)
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

void Common::updateRow(RowController *row)
{
  // TODO
}

void Common::setRow(int num, char *str, size_t sz)
{
  if (num < 0 || num > m_pCnfg->rowCount)  // if number is out of row numbers range
    return;                                // error

  // reallocation of memory
  // сhange the size of the rows to add a new row
  //
  m_pCnfg->pRowObj = realloc(m_pCnfg->pRowObj, sizeof(RowController) * (m_pCnfg->rowCount + 1));

  // copy size bytes of rows to the same object incremented by 1
  //
  memmove(&m_pCnfg->pRowObj[num + 1], &m_pCnfg->pRowObj[num], sizeof(RowController) * (m_pCnfg->rowCount - num));

  for (int i = num + 1; i <= m_pCnfg->rowCount; i++)
    m_pCnfg->pRowObj[i].index++;           // increase index

  m_pCnfg->pRowObj[num].index = num;       // set index
  m_pCnfg->pRowObj[num].size = sz;         // set size
  m_pCnfg->pRowObj[num].pLetter = malloc(sz + 1); // allocate memory for sz+1 bytes
  memcpy(m_pCnfg->pRowObj[num].pLetter, str, sz); // copy size bytes of string to pLetter (example: str is "s" - copy s to pLetter)
  m_pCnfg->pRowObj[num].pLetter[sz] = '\0';       // set EOF of row

  m_pCnfg->pRowObj[num].sizeRow = 0;              // zero size of row
  m_pCnfg->pRowObj[num].pVisualize = NULL;        // no visualize
  m_pCnfg->pRowObj[num].pClr = NULL;              // no colour
  m_pCnfg->pRowObj[num].commentClr = 0;           // no comment colour

  updateRow(&m_pCnfg->pRowObj[num]);

  m_pCnfg->rowCount++;                            // add 1 to rows number
  m_pCnfg->smear++;                               // new changes
}

void Common::setRowChar(RowController *row, int to, int ch)
{

}

void Common::setChar(int ch)
{
  if (m_pCnfg->configY == m_pCnfg->rowCount)  // if this is last line
  {
    setRow(m_pCnfg->rowCount, "", 0);         // set new row with zero position and empty
  }
  setRowChar(&m_pCnfg->pRowObj[m_pCnfg->configY], m_pCnfg->configX, ch); // set char to last position in last row
  m_pCnfg->configX++;                         // and increment row lenght for cursor
}
void Common::setNewline()
{
  // TODO
}

void Common::deleteChar()
{
  // TODO
}

void Common::save()
{
  // TODO
}

void Common::find()
{
  // TODO
}

void Common::drawRows(Adbfr* abfr);
{
  // TODO
}

void Common::drawStatusBar(Adbfr* abfr)
{
  // TODO
}

void Common::drawMessageBar(Adbfr* abfr)
{
  // TODO
}

void Common::scrolling()
{
  // TODO
}

void Common::statusMsg(const char *fmt, ...)
{
  va_list arg;         // for unknown number of parameters
  va_start(arg, fmt);  // initialize arg
  vsnprintf(cnfg.statusMessage, sizeof(cnfg.statusMessage), fmt, arg); // output parameters to statusMessage
  va_end(arg); // end
  cnfg.statusMessageTime = time(NULL); // gets time
}

void Common::updateScreen()
{
  scrolling();

  m_abfr = ADBFR_IMPL; // implement to NULL

  m_abfr.reallocateBfr("\x1b[?25l", 6); // reallocate data
  m_abfr.reallocateBfr("\x1b[H", 3);    // reallocate data

  /*
   * draw rows, message bar and status bar
   */
  drawRows(&m_abfr);
  drawStatusBar(&m_abfr);
  drawMessageBar(&m_abfr);

  /*
   * write to buff cursor | position
   */
  char buff[32];
  snprintf(buff, sizeof(buff), "\x1b[%d;%dH", (m_pCnfg->configY - m_pCnfg->disableRow) + 1, (m_pCnfg->rowX - m_pCnfg->disableClr) + 1);
  m_abfr.reallocateBfr(buff, strlen(buff));

  m_abfr.reallocateBfr("\x1b[?25h", 6);

  /*
   * update screen
   */
  write(STDOUT_FILENO, ab.b, ab.len);
  m_abfr.freeBfr(); // free memory
}

char* Common::callPrompt(char *prompt, void (*callback)(char*, int))
{
  size_t buffsize = 128;
  char* bfr = malloc(buffsize); // allocate memory

  size_t bufflen = 0;           // lenght
  bfr[0] = '\0';

  while (1)
  {
    statusMsg(prompt, bfr); // set prompt
    updateScreen();         // and update screen

    int key = tml.whatKey();  // read key

    if (key == DELETE_KEY || key == CTRL_KEY('h') || key == BACKSPACE)
    {
      if (bufflen != 0)         // if buffer is not empty
        bfr[--bufflen] = '\0';  // set end of row
    }
    else if (key == '\x1b')     // if this is ESC
    {
      statusMsg("");          // erase
      if (callback)           // if callback is not NULL
        callback(bfr, key);   // call func for callback which pointed by callback()
      free(bfr);              // free memory
      return NULL;            // and cancel
    }
    else if (key == '\r')     // if carriage return (move the cursor at the start of the line)
    {
      if (bufflen != 0)       // and bufflen is not empty
      {
        statusMsg("");        // clean message
        if (callback)
          callback(bfr, key); // and get callback
        return bfr;           // returning of buffer
      }
    }
    else if (!iscntrl(key) && key < 128) // checks, whether the argument, transmitted via the parameter сharacter, control character
    {
      /*
       * reallocation of buffer if needs
       */
      if (bufflen == buffsize - 1)
      {
        buffsize *= 2;
        bfr = realloc(bfr, buffsize);
      }
      bfr[bufflen++] = key; // write this key to buffer
      bfr[bufflen] = '\0';  // and end of row
    }

    if (callback)
      callback(bfr, key);   // call of callback
  }
}

void Common::moveCursor(int key)
{
  // instancing RowController
  // if empty - to zero position, else to the end of row
  //
  RowController* pRowctrl = (m_pCnfg->configY >= m_pCnfg->rowCount) ? NULL : &m_pCnfg->pRowObj[m_pCnfg->configY];

  switch (key)
  {
    case ARROW_LEFT:
      if (m_pCnfg->configX != 0)                                    // if horizontal position isn't zero
      {
        m_pCnfg->configX--;                                         // move left
      }
      else if (m_pCnfg->configY > 0)                                // else if there is at least 1 row
      {
        m_pCnfg->configY--;                                         // move to that row
        m_pCnfg->configX = m_pCnfg->pRowObj[m_pCnfg->configY].size; // and to the end of that row
      }
      break;
    case ARROW_RIGHT:
      if (pRowctrl && m_pCnfg->configX < pRowctrl->size)            // if there is row and if cursor is not in the end of row
      {
        m_pCnfg->configX++;                                         // move cursor right along of row
      }
      else if (pRowctrl && m_pCnfg->configX == pRowctrl->size)      // if there is row and cursor in the end of this row
      {
        m_pCnfg->configY++;                                         // move to next row
        E.cx = 0;                                                   // on zero position
      }
      break;
    case ARROW_UP:
      if (m_pCnfg->configY != 0)                                    // if there is at least 1 row
      {
        m_pCnfg->configY--;                                         // move up
      }
      break;
    case ARROW_DOWN:
      if (m_pCnfg->configY < m_pCnfg->rowCount)                     // if cursor is not on last row
      {
        m_pCnfg->configY++;                                         // move down
      }
      break;
  }
}

void Common::processingKeypress()
{
  static int sQuitCounter = EDITORRMEND_QUIT_COUNTER;                // counter clicking for exit

  int key = whatKey();                                               // read key

  switch (key)
  {
    case '\r':                                                       // if carriage return (Enter key)
      setNewline();                                                   // set newline
      break;

    case CTRL_KEY('q'):
      if (m_pCnfg->smear && sQuitCounter > 0)                        // if there is any changes and counter > 0
      {
        statusMsg("! File was changed and unsaved and data can be lost after exiting. "
                  "Press Ctrl-Q %d more times to exit.", sQuitCounter);
        sQuitCounter--;                                              // counter decrement
        return;
      }
      write(STDOUT_FILENO, "\x1b[2J", 4);
      write(STDOUT_FILENO, "\x1b[H", 3);
      exit(0);
      break;

    case CTRL_KEY('s'):
      save();                                                       // TODO: save changes
      break;

    case HOME_KEY:
    m_pCnfg->configX = 0;                                           // to the row beginning
      break;

    case END_KEY:
      if (m_pCnfg->configY < m_pCnfg->rowCount)                     // if not last row
        m_pCnfg->configX = m_pCnfg->pRowObj[m_pCnfg->configY].size; // to the end of row
      break;

    case CTRL_KEY('f'):
      find();                                                       // find func
      break;

    case BACKSPACE:
    case CTRL_KEY('h'):
    case DELETE_KEY:
      if (key == DELETE_KEY)
        moveCursor(ARROW_RIGHT);                                    // move cursor right
      deleteChar();                                                 // delete char
      break;

    // page up/down
    //
    case PAGE_UP:
    case PAGE_DOWN:
      {
        if (key == PAGE_UP)
        {
          m_pCnfg->configY = m_pCnfg->disableRow;                    // move page up
        }
        else if (key == PAGE_DOWN)
        {
          m_pCnfg->configY = m_pCnfg->disableRow + m_pCnfg->enableRow - 1; // move page down
          if (m_pCnfg->configY > m_pCnfg->rowCount)
            m_pCnfg->configY = m_pCnfg->rowCount;
        }

        int times = m_pCnfg->enableRow;
        while (times--)
          moveCursor(key == PAGE_UP ? ARROW_UP : ARROW_DOWN);
      }
      break;

    case ARROW_UP:
    case ARROW_DOWN:
    case ARROW_LEFT:
    case ARROW_RIGHT:
      moveCursor(key);
      break;

    case CTRL_KEY('l'):
    case '\x1b':
      break;

    default:
      setChar(key);   // just write chars
      break;
  }

  sQuitCounter = EDITORRMEND_QUIT_COUNTER;
}
