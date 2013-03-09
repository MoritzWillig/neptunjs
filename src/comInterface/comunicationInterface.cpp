/* 
 * File:   comunicationInterface.cpp
 * Author: Moritz Willig
 *
 * Created on March 9, 2013, 18:43 PM
 */

#include <string>
#include <sstream>
#include <iostream>
#include "comunicationInterface.h"

using namespace std;

/**
 * Determines if the output follows the cgi standart or uses the neptunjs protocol
**/
bool cgiMode=false;

/**
 * Creates the standart output for all neptunjs applications. The result is influenced
 * by the cgiMode flag which, when set to true, creates output for cgi applications.
 * @param statuscode Status about the application and script execution
 * @param output Additional information or application output
 * @return Returns a formated result which fits the neptunjs or cgi standart.
 */
string formatOutput(JSOutputMsg statuscode, string output) {
    stringstream ios;
    
    string statusMsg="";
    switch (statuscode) {
        case OM_NO_ERROR:      statusMsg="OK"; break;
        case OM_EXEC_FILE:     statusMsg="No exec file given"; break;
        case OM_NO_FILE:       statusMsg="No file found"; break;
        case OM_INVALID_FLAG:  statusMsg="Unknown flag"; break;
        case OM_INVALID_PARAM: statusMsg="Invalid parameter"; break;
        case OM_JS_ERROR:      statusMsg="Uncaught JS Error"; break;
        case OM_INVALID_LOGIN: statusMsg="Invalid login"; break;
        case OM_OUT_OF_MEM:    statusMsg="Out of Memory"; break;
        case OM_CANT_EXECUTE_NEPTUNJS: statusMsg="Can not execute NeptunJS"; break;
        case OM_UNKNOWN_ERROR: statusMsg="An unknown error occurced"; break;
    }
    
    if (cgiMode) {
        if (statuscode==OM_NO_ERROR) {
            ios<<output;
        } else {
            ios<<"Content-Type: text/plain\r\n\r\n";
            ios << statuscode << " " << statusMsg << "\nOUTPUT " << output.length() << "\n" << output <<"\n";
        }
    } else {
        ios << statuscode << " " << statusMsg << "\nOUTPUT " << output.length() << "\n" << output <<"\n";
    }
    
    return ios.str();
}