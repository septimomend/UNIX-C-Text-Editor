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

void ConfigurationController::updateRow(RowController *row)
{
  // TODO
}

void ConfigurationControllern::setRow(int num, char *str, size_t sz)
{
  if (num < 0 || num > m_pCnfg->rowCount)  // if number is out of row numbers range
    return;                                // error

  // reallocation of memory
  // сhange the size of the rows to add a new row
  //
  m_pCnfg->pRowObj = realloc(m_pCnfg->pRowObj, sizeof(RowController) * (m_pCnfg->rowCount + 1));

  // copy size bytes of rows to the same object incremented by 1
  //
  memmove(&m_pCnfg->pRowObj[num + 1], &m_pCnfg->pRowObj[num], sizeof(RowController) * (m_pCnfg->rowCount - num));

  for (int i = num + 1; i <= m_pCnfg->rowCount; i++)
    m_pCnfg->pRowObj[i].index++;           // increase index

  m_pCnfg->pRowObj[num].index = num;       // set index
  m_pCnfg->pRowObj[num].size = sz;         // set size
  m_pCnfg->pRowObj[num].pLetter = malloc(sz + 1); // allocate memory for sz+1 bytes
  memcpy(m_pCnfg->pRowObj[num].pLetter, str, sz); // copy size bytes of string to pLetter (example: str is "s" - copy s to pLetter)
  m_pCnfg->pRowObj[num].pLetter[sz] = '\0';       // set EOF of row

  m_pCnfg->pRowObj[num].sizeRow = 0;              // zero size of row
  m_pCnfg->pRowObj[num].pVisualize = NULL;        // no visualize
  m_pCnfg->pRowObj[num].pClr = NULL;              // no colour
  m_pCnfg->pRowObj[num].commentClr = 0;           // no comment colour

  updateRow(&m_pCnfg->pRowObj[num]);

  m_pCnfg->rowCount++;                            // add 1 to rows number
  m_pCnfg->smear++;                               // new changes
}

void ConfigurationController::setRowChar(RowController *row, int to, int ch)
{
  // TODO
}
