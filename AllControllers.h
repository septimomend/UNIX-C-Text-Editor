// AllControllers.h -- header file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 30.06.2017
 *
 */

#include "stdafx.h"
#include "ConfigurationController"

class AllControllers : public ConfigurationController
{
public:
  AllControllers(); // cstr
  // TODO: public data

private:
  SyntaxController snx[] = {
                            {"c", pFileExtension, pKeywords,
                              "//", "/*", "*/",
                              CLR_COLORFUL_NUMBERS | CLR_COLORFUL_STRINGS},
                           };

  ConfigurationController configObj;

  #define _SNX_ (sizeof(snx) / sizeof(snx[0]))
}
