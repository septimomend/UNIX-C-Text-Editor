// stdafx.h -- precompiled header
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   27.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

 #define _DEFAULT_SOURCE
 #define _BSD_SOURCE
 #define _GNU_SOURCE

 #include <cctype>
 #include <errno.h>
 #include <fcntl.h>
 #include <iostream>
 #include <stdarg.h>
 #include <cstdlib>
 #include <cstring>
 #include <string>
 #include <sys/ioctl.h>
 #include <sys/types.h>
 #include <termios.h>
 #include <ctime>
 #include <unistd.h>

// defines
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#define EDITORMEND_VERSION "0.0.1"
#define EDITORMEND_TBL_STOP 5
#define EDITORRMEND_QUIT_COUNTER 2

#define CTRL_KEY(k) ((k) & 0x1f)

#define ADBFR_IMPL {NULL, 0}

enum controlKeys
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
  CLR_NORMAL = 0,
  CLR_COMMENT,
  CLR_MLCOMMENT,
  CLR_KEYWORD1,
  CLR_KEYWORD2,
  CLR_STRING,
  CLR_NUMBER,
  CLR_MATCH
};

#define CLR_COLORFUL_NUMBERS (1<<0)
#define CLR_COLORFUL_STRINGS (1<<1)
