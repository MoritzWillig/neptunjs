/* 
 * File:   BasicAddin.h
 * Author: moritz
 *
 * Created on February 18, 2013, 10:03 PM
 */

#ifndef BASICADDIN_H
#define	BASICADDIN_H

#include "../../Permission.h"

class BasicAddin {
public:
    BasicAddin();
    void importFromPermission(const Permission& permission);
    void clearRights();
    
    struct Rights {
        bool isFile;
        bool read;
        bool write;
        bool execute;
    };
    Rights rights;
};

#endif	/* BASICADDIN_H */

