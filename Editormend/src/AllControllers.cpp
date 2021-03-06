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
  configObj.pSyntaxObj = NULL;
  if (configObj.pFilename == NULL)
    return;

  for (unsigned int j = 0; j < SNX_SZ; j++)
  {
    SyntaxController *sctrl = &snx[j];              // initialize syntax instance
    unsigned int i = 0;
    while (sctrl->ppFileAccordance[i])
    {
      char *ac = strstr(configObj.pFilename, sctrl->ppFileAccordance[i]);  // char that accordance with pFilename
      if (ac != NULL)                                                      // if that char is accordanced with filename
      {
        int acsz = strlen(sctrl->ppFileAccordance[i]);
        if (sctrl->ppFileAccordance[i][0] != '.' || ac[acsz] == '\0')      // if met point of file expansion, i.e. filename.<type> or end of filename without expansion
        {
          configObj.pSyntaxObj = sctrl;                                    // copy data to main syntax object

          int pastRows;
          // colorize rows before knowing of filename and expansion
          //
          for (pastRows = 0; pastRows < configObj.rowCount; pastRows++)
          {
            configObj.pSyntaxObj->updateSyntax(&configObj.pRowObj[pastRows]);
          }
          return;
        }
      }
      i++;
    }
  }
}

void Common::setChar(int ch)
{
  if (configObj.configY == configObj.rowCount)                                        // if this is last line
    configObj.setRow(configObj.rowCount, "", 0);                                      // set new row with zero position and empty
  configObj.setRowChar(&configObj.pRowObj[configObj.configY], configObj.configX, ch); // set char to last position in last row
  configObj.configX++;                                                                // and increment row lenght for cursor
}

void Common::setNewline()
{
  if (configObj.configX == 0)                                                         // if this is zero position in row
    configObj.setRow(configObj.configY, "", 0);                                       // set empty line
  else
  {
    RowController *row = &configObj.pRowObj[configObj.configY];                       // get line
    // and set newline with moved data sized size - configX
    //
    configObj.setRow(configObj.configY + 1, &row->pLetter[configObj.configX], row->size - configObj.configX);
    row = &configObj.pRowObj[configObj.configY];
    row->size = configObj.configX;                                                    // update size
    row->pLetter[row->size] = '\0';                                                   // and add end of line symbol
    configObj.updateRow(row);
  }
  configObj.configY++;                                                                // increase line count
  configObj.configX = 0;                                                              // set position at line start
}

void Common::deleteChar()
{
  if (configObj.configY == configObj.rowCount)            // can't to delete next char
    return;
  if (configObj.configX == 0 && configObj.configY == 0)   // nothing for deleting
    return;

  RowController *row = &configObj.pRowObj[configObj.configY];
  if (configObj.configX > 0)                              // if row is not empty
  {
    configObj.eraseLetterInRow(row, configObj.configX - 1); // delete this char
    configObj.configX--;                                    // and decrease length of row
  }
  else
  {
    configObj.configX = configObj.pRowObj[configObj.configY - 1].size;// end of row
    // connect string to row (shift up)
    //
    configObj.str2Row(&configObj.pRowObj[configObj.configY - 1], row->pLetter, row->size);
    eraseRow(configObj.configY);                                      // and erase row
    configObj.configY--;                                              // length is decreasing
  }
}
