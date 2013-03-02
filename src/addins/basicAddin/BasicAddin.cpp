/* 
 * File:   BasicAddin.cpp
 * Author: moritz
 * 
 * Created on February 18, 2013, 10:03 PM
 */

#include "BasicAddin.h"

BasicAddin::BasicAddin() {
    clearRights();
}

void BasicAddin::importFromPermission(const Permission& permission) {
    rights.execute=permission.execute;
    rights.isFile=permission.isFile;
    rights.read=permission.read;
    rights.write=permission.write;
}

void BasicAddin::clearRights() {
    rights.execute=false;
    rights.read=false;
    rights.write=false;
}