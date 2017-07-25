// RowController.cpp -- source file
/*
 * Author: Ivan Chapkailo (septimomend)
 * Date:   25.07.2017
 *
 * © 2017 Ivan Chapkailo. All rights reserved
 * e-mail: chapkailo.ivan@gmail.com
 */

#include "stdafx.h"
#include "RowController.h"

RowController::RowController()
{
}

void RowController::freeThisRow()
{
  // freeing memory when row will be deleting
  //
  free(this->pVisualize);
  free(this->pLetter);
  free(this->pClr);
}
