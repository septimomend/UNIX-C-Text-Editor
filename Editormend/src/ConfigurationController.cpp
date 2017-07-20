// ConfigurationController.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   02.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "ConfigurationController.h"

ConfigurationController::ConfigurationController()
{
}

struct termios ConfigurationController::getTermios() const
{
  return baseTermiosObj;
}
