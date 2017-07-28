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
  int tbl = 0;                              // tabulated counter
  int j;
  for (j = 0; j < row->size; j++)
  {
    if (row->pLetter[j] == '\t')            // if tabulate symbol is meeting
      tbl++;                                // increment tabulated counter
  }

  free(row->pVisualize);                    // free memory
  row->pVisualize = malloc(row->size + tbl*(EDITORMEND_TBL_STOP - 1) + 1);  // allocate new memory with adding of tabulation symbol

  int indx = 0;
  for (j = 0; j < row->size; j++)
  {
    if (row->pLetter[j] == '\t')                                  // if inputed TAB
    {
      row->pVisualize[indx++] = ' ';                              // fill it with spaces
      while (indx % EDITORMEND_TBL_STOP != 0)                     // as many time as
        row->pVisualize[indx++] = ' ';                            // macros EDITORMEND_TBL_STOP lets
    }
    else
      row->pVisualize[indx++] = row->pLetter[j];                  // else set other letter
  }
  row->pVisualize[indx] = '\0';                                   // set EOF symbol after row is end
  row->sizeRow = indx;                                            // and row size

  pSyntaxObj->updateSyntax(row);                                  // update syntax of this row
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
  if (to < 0 || to > row->size)   // if it is out of row size
    to = row->size;               // set row size fot it
  row->pLetter = realloc(row->pLetter, row->size + 2);  // reallocate memory for new char
  memmove(&row->pLetter[to + 1], &row->pLetter[to], row->size - to + 1); // shift others chars
  row->size++;           // increase row size
  row->pLetter[to] = ch; // set char
  updateRow(row);        // update row
  this->smear++;         // new changes
}

int ConfigurationController::configX2RowX(RowController *row, int cnfgX)
{
  int rwX = 0;
  int j;
  // just calculate cursor position in row with adding tabs
  //
  for (j = 0; j < cnfgX; j++)
  {
    if (row->pLetter[j] == '\t')                                      // if there is tabulate symbol
      rwX += (EDITORMEND_TBL_STOP - 1) - (rwX % EDITORMEND_TBL_STOP); // add this tab space to rowX value
    rwX++;                                                            // increment of rowX
  }
  return rwX;
}

int ConfigurationController::rowX2configX(RowController *row, int rwX)
{
  int currentRowX = 0;
  int cnfgX;
  for (cnfgX = 0; cnfgX < row->size; cnfgX++)
  {
    if (row->pLetter[cnfgX] == '\t')                                                  // if tabulate
      currentRowX += (EDITORMEND_TBL_STOP - 1) - (currentRowX % EDITORMEND_TBL_STOP); // add this space
    currentRowX++;                                                                    // increment row X pos

    if (currentRowX > rwX)                                                            // if current pos is more than is it
      return cnfgX;                                                                   // return cnfgX
  }
  return cnfgX;                                                                       // cnfgX does not take into account a tabulate symbols
}

void eraseRow(int isHere)
{
  if (isHere < 0 || isHere >= this->rowCount) // if position is out of rows
    return;                                   // abort
  this->pRowObj[isHere].freeThisRow();        // free memory
  memmove(&this->pRowObj[isHere], &this->pRowObj[isHere + 1], sizeof(RowController) * (this->rowCount - isHere - 1));
  for (int j = isHere; j < (this->rowCount - 1); j++) // erase
    this->pRowObj[j].index--;
  this->rowCount--;                                   // decrease rows
  this->smear++;                                      // changes
}

void ConfigurationController::eraseLetterInRow(RowController *row, int isHere)
{
  // TODO
}

void ConfigurationController::str2Row(RowController *row, char *str, size_t sz)
{
  // TODO
}
