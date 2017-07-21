// AllControllers.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   30.06.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "AllControllers.h"

using namespace std;

// default csrt
//
AllControllers::AllControllers()
{
}

ConfigurationController* AllControllers::getConfigObj() const
{
  return &configObj;
}

void AllControllers::pickSyntaxClr()
{
  // TODO
}
