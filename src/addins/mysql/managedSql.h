/* 
 * File:   managedFile.h
 * Author: Moritz Willig
 *
 * Created on August 19, 2012, 6:39 AM
 */


#ifndef MANAGEDFILE_H
#define	MANAGEDFILE_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "../basicAddin/BasicAddin.h"

#include "mysql_driver.h"
#include "mysql_connection.h"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"


using namespace std;

class ManagedSql : public BasicAddin {
public:
    ManagedSql();
    ~ManagedSql();
    
    bool isCreated(); //got a valid driver instance
    bool isConnected(); //got an valid connection
    
    bool connect(string adress, string user, string password);
    bool close();
    
    void setCommand(string s);
    string getCommand();
    bool execute();
    void executeQuery(); //fills in results
    int executeUpdate(); //returns affected rows
    
    sql::ResultSet* getLastResult();
private:
    void prepareQuery();
    string lastCommand;
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
};

#endif	/* MANAGEDFILE_H */