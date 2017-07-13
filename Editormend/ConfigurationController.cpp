// ConfigurationController.cpp -- source file
/*
 *
 * Author: septimomend (Ivan Chapkailo)
 *
 * 02.07.2017
 *
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
