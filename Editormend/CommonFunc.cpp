// CommonFunc.cpp -- source file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 02.07.2017
 *
 */

#include "stdafx.h"
#include "CommonFunc.h"


Common::Common(AllControllers* all) : *m_cnfg(all->getConfigObj())
{
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
  snprintf(buff, sizeof(buff), "\x1b[%d;%dH", (m_cnfg->configY - m_cnfg->disableRow) + 1, (m_cnfg->rowX - m_cnfg->disableClr) + 1);
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

void Common::moveCursor(int key)
{
  // TODO
}

void Common::processingKeypress()
{
  // TODO
}
