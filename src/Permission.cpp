/* 
 * File:   Permission.cpp
 * Author: moritz
 * 
 * Created on October 15, 2012, 2:46 AM
 */

#include "Permission.h"
#include "addins/file/managedFile.h"
#include <iostream>

Permission::Permission() {
    this->isFile=false;
    this->protocol="";
    this->trace="";
    this->read=false;
    this->write=false;
    this->execute=false;
}

Permission::Permission(const Permission& rhs) {
    this->isFile=rhs.isFile;
    this->protocol=rhs.protocol;
    this->trace=rhs.trace;
    this->read=rhs.read;
    this->write=rhs.write;
    this->execute=rhs.execute;
}

bool Permission::restrictTrace(string newTrace) {
    if ((!isFile) && (checkPermission(newTrace))) {
        trace=newTrace;
        return true;
    } else {
        return false;
    }
}

void Permission::lowerRights(bool lowerRead, bool lowerWrite, bool lowerExecute) {
    if (lowerRead   ) { read   =false; }
    if (lowerWrite  ) { write  =false; }
    if (lowerExecute) { execute=false; }
}

bool Permission::checkPermission(string newTrace) {
    if (isFile) {
        return (ManagedFile::absolutePath(trace)==ManagedFile::absolutePath(newTrace));
    } else {
        string sx=ManagedFile::absolutePath(trace);
        string sy=ManagedFile::absolutePath(newTrace);

        return (sy.substr(0,sx.length())==sx);
    }
}


PermissionCollection::PermissionCollection() {
    
}

PermissionCollection::~PermissionCollection() {

}

PermissionSet* PermissionCollection::getPermissions(string protocol) {
    map<string,PermissionSet*>::iterator permsI = perms.find(protocol);
    return (permsI==perms.end())?NULL:permsI->second;
}

void PermissionCollection::addPermission(string protocol, Permission* perm) {
    PermissionSet* ps = getPermissions(protocol);
    if (ps==NULL) {
        ps = new PermissionSet();
        perms[protocol]=ps;
    }
    
    ps->push_back(perm);
}

