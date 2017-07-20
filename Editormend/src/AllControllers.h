// AllControllers.h -- header file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   30.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#pragma once

#include "stdafx.h"
#include "ConfigurationController.h"

class AllControllers : public ConfigurationController
{
public:
  AllControllers(); // cstr
  ConfigurationController getConfigObj() const;
  // TODO: public data


private:
  SyntaxController snx[] = {
                            {"c", pFileExtension, pKeywords,
                              "//", "/*", "*/",
                              CLR_COLORFUL_NUMBERS | CLR_COLORFUL_STRINGS},
                           };

  ConfigurationController configObj;

  #define _SNX_ (sizeof(snx) / sizeof(snx[0]))
};
