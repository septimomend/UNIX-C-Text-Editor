// Terminal.cpp -- source file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 30.06.2017
 *
 */

#include "stdafx.h"
#include "Terminal.h"

Terminal::Terminal() // cstr
{
}

/*
 * 0 - STDIN_FILENO - standard input descriptor
 * 1 - STDOUT_FILENO - standard output descriptor
 * 2 - STDERR_FILENO - standard errors output descriptor
 */

void Terminal::emergencyDestruction(const char* str)
{
  write(STDOUT_FILENO, "\x1b[2J", 4); // write clr code to file
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(str);
  exit(1);  // exit with error
}

void Terminal::rowModeOff()
{
  AllControllers all;
  ConfigurationController* configObj = all.getConfigObj();
  struct termios* termObj = configObj->getTermios();

  // the change will occur after all output written to STDIN_FILENO is transmitted,
  // and all input so far received but not read will be discarded before the change is made
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, termObj) == -1)
    emergencyDestruction("tcsetattr");
}

void Terminal::rowModeOn()
{
  AllControllers all;
  ConfigurationController* configObj = all.getConfigObj();
  struct termios* termObj = configObj->getTermios();

  if (tcgetattr(STDIN_FILENO, termObj) == -1)
    emergencyDestruction("tcgetattr");
  atexit(rowModeOff);

  struct termios raw = *termObj;
  // setting flags
  //
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST); // Post-process output
  raw.c_cflag |= (CS8); // Character size 8 bits
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
}

int Terminal::whatKey() // defines key pressing
{
  int countRD;
  char c;
  while ((countRD = read(STDIN_FILENO, &c, 1)) != 1)  // read 1 byte from input device and write to c
  {
    if (countRD == -1 && errno != EAGAIN)
      emergencyDestruction("read");
  }

  if (c == '\x1b') // if this is the escape key
  {
    char sequence[3];

    if (read(STDIN_FILENO, &sequence[0], 1) != 1) // if no errors
      return '\x1b';
    if (read(STDIN_FILENO, &sequence[1], 1) != 1)
      return '\x1b';

    // this is escape-sequence
    //          \x1b[...m
    // where ... is numbers of parameters
    // more on https://en.wikipedia.org/wiki/Escape_sequences_in_C
    //
    if (sequence[0] == '[')
    {
      if (sequence[1] >= '0' && sequence[1] <= '9')
      {
        if (read(STDIN_FILENO, &sequence[2], 1) != 1)
          return '\x1b'; // if escape calls 3rd time - exit
        if (sequence[2] == '~')
        {
          switch (sequence[1])
          {
            case '1':
              return HOME_KEY;
            case '3':
              return DELETE_KEY;
            case '4':
              return END_KEY;
            case '5':
              return PAGE_UP;
            case '6':
              return PAGE_DOWN;
            case '7':
              return HOME_KEY;
            case '8':
              return END_KEY;
          }
        }
      }
      else  // else if sequence[1] is not numbers
      {
        switch (sequence[1])
        {
          case 'A':
            return ARROW_UP;
          case 'B':
            return ARROW_DOWN;
          case 'C':
            return ARROW_RIGHT;
          case 'D':
            return ARROW_LEFT;
          case 'H':
            return HOME_KEY;
          case 'F':
            return END_KEY;
        }
      }
    }
    else if (sequence[0] == 'O')
    {
      switch (sequence[1])
      {
        case 'H':
          return HOME_KEY;
        case 'F':
          return END_KEY;
      }
    }
    return '\x1b';
  }
  else
    return c;
}

int Terminal::getCursorPosition(int *row, int *column) // returns cursor position
{
  // TODO
}

int Terminal::getWindowSize(int *row, int *column) // returns size of window
{
  // TODO
}
