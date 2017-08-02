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
  {
    configObj.setRow(configObj.rowCount, "", 0);                                                // set new row with zero position and empty
  }
  configObj.setRowChar(&configObj.pRowObj[configObj.configY], configObj.configX, ch); // set char to last position in last row
  configObj.configX++;                                                                // and increment row lenght for cursor
}

void Common::setNewline()
{
  // TODO
}

void Common::deleteChar()
{
  // TODO
}
