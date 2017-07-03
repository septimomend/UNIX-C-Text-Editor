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
  // TODO
}

int Terminal::getCursorPosition(int *row, int *column) // returns cursor position
{
  // TODO
}

int Terminal::getWindowSize(int *row, int *column) // returns size of window
{
  // TODO
}
