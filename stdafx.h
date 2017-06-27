// precompiled header
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 27.06.2017
 *
 */

 #define _DEFAULT_SOURCE
 #define _BSD_SOURCE
 #define _GNU_SOURCE

 #include <ctype.h>
 #include <errno.h>
 #include <fcntl.h>
 #include <iostream>
 #include <stdarg.h>
 #include <cstdlib>
 #include <string>
 #include <sys/ioctl.h>
 #include <sys/types.h>
 #include <termios.h>
 #include <ctime>
 #include <unistd.h>

// defines

#define SEPT_CPP_EDITOR_VERSION "0.0.1"
#define SEPT_TAB_STOP 8
#define SEPT_QUIT_TIMES 2 // click times for exit

#define CTRL_KEY(k) ((k) & 0x1f)

enum keys
{
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DELETE_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

enum colorful 
{
  HL_NORMAL = 0,
  HL_COMMENT,
  HL_MLCOMMENT,
  HL_KEYWORD1,
  HL_KEYWORD2,
  HL_STRING,
  HL_NUMBER,
  HL_MATCH
};
