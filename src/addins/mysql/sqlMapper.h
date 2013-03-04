/* 
 * File:   sqlMapper.h
 * Author: moritz
 *
 * Created on September 17, 2012, 4:40 AM
 */

#ifndef SQLMAPPER_H
#define	SQLMAPPER_H

#include "../../mapper/macros.h"
#include "../../../libs/v8_64bit/include/v8.h"

#include "mysql_connection.h"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

using namespace v8;

namespace addin_sql {
    
namespace {

extern Persistent<Function> v8sql;

JS_METHOD(sqlConstructor); //void ([adress,user,password])
JS_METHOD(sqlDestructor); //void ()

JS_METHOD(sqlConnect);//bool (adress,user,password)
JS_METHOD(sqlClose);//bool ()

JS_METHOD(sqlIsCreated);//bool ()
JS_METHOD(sqlIsConnected);//bool ()

JS_METHOD(sqlSetCommand); //undef (string)
JS_METHOD(sqlGetCommand); //undef (string)
JS_METHOD(sqlQuery);//[[val]] ([string],["all"|"line"|"single"])
JS_METHOD(sqlExecute);//bool ([string])
JS_METHOD(sqlUpdate);//int ([string])

v8::Handle<v8::Array> mapResult(sql::ResultSetMetaData* meta, sql::ResultSet* res);

}

void load();
void unload();
}

#endif	/* SQLMAPPER_H */

