/**************************************************************************************
    Author: Mordechai Ben Shimon
    Creation date :  01/01/23
    Last modified date:  --
    Description :  General Errors.
***************************************************************************************/
#ifndef __ERRORS_H__
#define __ERRORS_H__

typedef enum
{
    /* General Errors */
    ERR_OK = 0,
    ERR_FINISH_SUCCESS,
    ERR_FINISH_FAILURE,
    ERR_NOT_FINISH,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_WRONG_INDEX,
    ERR_ILLEGAL
} Errors;

// Functions header definition:
void HandleErr(Errors errNum, char* msg);

#endif /*__ERRORS_H__*/