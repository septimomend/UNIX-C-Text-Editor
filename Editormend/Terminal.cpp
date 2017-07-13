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
  ConfigurationController* configObj = all.getConfigObj();
  struct termios* termObj = configObj->getTermios();
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
  // the change will occur after all output written to STDIN_FILENO is transmitted,
  // and all input so far received but not read will be discarded before the change is made
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, termObj) == -1)
    emergencyDestruction("tcsetattr");
}

void Terminal::rowModeOn()
{
  if (tcgetattr(STDIN_FILENO, termObj) == -1)
    emergencyDestruction("tcgetattr");
  atexit(rowModeOff);

  // setting flags
  //
  termOb->c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  termOb->c_oflag &= ~(OPOST); // Post-process output
  termOb->c_cflag |= (CS8); // Character size 8 bits
  termOb->c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  termOb->c_cc[VMIN] = 0;
  termOb->c_cc[VTIME] = 1;
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
        {Termios
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
          case 'A':  ConfigurationController
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
  char buff[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) // output 4 bytes to standard output device
    return -1;

  while (i < sizeof(buff) - 1)
  {
    if (read(STDIN_FILENO, &buff[i], 1) != 1) // read from ouput to buff 1 byte
      break;
    if (buff[i] == 'R')
      break;
    i++;
  }
  buff[i] = '\0';

  if (buff[0] != '\x1b' || buff[1] != '[') // if wrong data
    return -1;
  if (sscanf(&buff[2], "%d;%d", row, column) != 2) // read data from buff and check number of fields
    return -1;

  return 0;
}

int Terminal::getWindowSize(int *row, int *column) // returns size of window
{
  struct winsize ws; // #include <sys/ioctl.h> - http://www.delorie.com/djgpp/doc/libc/libc_495.html

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) // do operation TIOCGWINSZ in standard output and fill
                                                                     // window's size to ws
  {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      return -1;
    return getCursorPosition(row, column);
  }
  else
  {
    *column = ws.ws_col;
    *row = ws.ws_row;
    return 0;
  }
}
