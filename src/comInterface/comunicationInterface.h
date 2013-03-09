/* 
 * File:   comunicationInterface.h
 * Author: moritz
 *
 * Created on March 9, 2013, 7:08 PM
 */

#ifndef COMUNICATIONINTERFACE_H
#define	COMUNICATIONINTERFACE_H

#include <string>

/**
 * Unified message codes for NeptunJS applications
**/
enum JSOutputMsg {
    OM_NO_ERROR=0,
    OM_EXEC_FILE=1,
    OM_NO_FILE=2,
    OM_INVALID_FLAG=3,
    OM_INVALID_PARAM=4,
    OM_JS_ERROR=5,
    OM_INVALID_LOGIN=6,
    OM_OUT_OF_MEM=7,
    OM_CANT_EXECUTE_NEPTUNJS=8,
    OM_UNKNOWN_ERROR=9
};

extern bool cgiMode;
extern std::string formatOutput(JSOutputMsg statuscode, std::string output);

#endif	/* COMUNICATIONINTERFACE_H */

