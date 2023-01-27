/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  21/01/23
    Description :  General Errors.
***************************************************************************************/

#include <stdio.h>

#include "Errors.h"

const char* ErrDescription[] =
{
    /* General Errors - Description */

    "Finish success",
    "Finish failure",
    "Not finish",
     "OK",
    "General Error",
    "Initialization error",
    "Allocation error",
    "Wrong index"
};

void HandleErr(Errors errNum, char* msg)
{
    if (errNum)
    {
        printf("ErrNum=%d, ErrDescription=%s, msg=%s\n",
            errNum, ErrDescription[errNum], msg);
    }

}
