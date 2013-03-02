/* 
 * File:   Permission.h
 * Author: moritz
 *
 * Created on October 15, 2012, 2:46 AM
 */

#ifndef PERMISSION_H
#define	PERMISSION_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class Permission {
public:
    Permission();
    Permission(const Permission& rhs);
    
    bool isFile;
    string protocol;
    string trace;
    bool read;
    bool write;
    bool execute;
    
    bool restrictTrace(string newTrace);
    void lowerRights(bool lowerRead, bool lowerWrite, bool lowerExecute);
    bool checkPermission(string newTrace);
};

typedef vector<Permission*> PermissionSet;

struct PermissionCollection {
public:
    PermissionCollection();
    ~PermissionCollection();
    
    PermissionSet* getPermissions(string protocol);
    void addPermission(string protocol, Permission* perm);
    
    map<string,PermissionSet*> perms;
private:
    
};

#endif	/* PERMISSION_H */

