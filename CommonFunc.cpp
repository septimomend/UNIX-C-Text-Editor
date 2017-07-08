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


Common::Common() // cstr
{
}

void Common::statusMsg(const char *fmt, ...)
{
  AllControllers all;
  ConfigurationController cnfg = all.getConfigObj();
  va_list arg;         // for unknown number of parameters
  va_start(arg, fmt);  // initialize arg
  vsnprintf(cnfg.statusMessage, sizeof(cnfg.statusMessage), fmt, arg); // output parameters to statusMessage
  va_end(arg); // end
  cnfg.statusMessageTime = time(NULL); // gets time
}

void Common::updateScreen()
{

}

char* Common::callPrompt(char *prompt, void (*callback)(char *, int))
{

}
