/* 
 * File:   addins.h
 * Author: Moritz Willig
 *
 * Created on September 28, 2012, 12:01 PM
 */

#ifndef ADDINS_H
#define	ADDINS_H

//Insert all addins in the list below and in the loader functions
#include "abstractNative.h"
#include "addins/permission/permissionMapper.h"
#include "addins/file/fileMapper.h"
#include "addins/mysql/sqlMapper.h"
#include "addins/outputBuffer/outputBufferMapper.h"

namespace addins {
    void load() {
        addin_AbstractNative::load();
        addin_permission::load();
        addin_file::load();
        addin_sql::load();
        addin_outputBuffer::load();
    }
    
    void unload() {
        addin_AbstractNative::unload();
        addin_permission::unload();
        addin_file::unload();
        addin_sql::unload();
        addin_outputBuffer::unload();
    }
}

#endif	/* ADDINS_H */

