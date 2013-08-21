/*
 * Author: Moritz Willig
 * Date:   21.8.2012
 * 
 * Managed File which allows modifying files in a specified folder, but prevents
 * operations outside of the given folder.
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <cstring>

#include "managedSql.h"

using namespace std;

ManagedSql::ManagedSql() {
    driver=NULL;
    con=NULL;
    lastCommand="";
    
    driver=get_driver_instance();
    /*
    try {
    } catch (sql::SQLException &e) {
        cout<<"Error"<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<endl;
        cout<<e.what()<<e.getErrorCode()<<e.getSQLState()<<endl;
    }
    */
}

ManagedSql::~ManagedSql() {
    lastCommand="";
    close();
    //if (isCreated()) { delete driver; } can't delete driver
}
    
bool ManagedSql::isCreated() {
    return (driver!=NULL);
}

bool ManagedSql::isConnected() {
    return (con!=NULL);
}

//"tcp://127.0.0.1:3306","root","root"
bool ManagedSql::connect(string adress, string user, string password) {
    if (isConnected()) { close(); }
    
    con = driver->connect(adress,user,password);
    //con->setSchema("test");
    stmt=con->createStatement();
}

bool ManagedSql::close() {
    if (isConnected()) {
        delete con; con=NULL;
        return true;
    } else {
        return false;
    }
}

void ManagedSql::setCommand(string s) {
    lastCommand=s;
}

string ManagedSql::getCommand() {
    return lastCommand;
}

bool ManagedSql::execute() {
    prepareQuery();
    stmt->execute(lastCommand);
}

void ManagedSql::executeQuery() {
    prepareQuery();
    res=stmt->executeQuery(lastCommand);
}

int ManagedSql::executeUpdate() {
    prepareQuery();
    return stmt->executeUpdate(lastCommand);
}

sql::ResultSet* ManagedSql::getLastResult() {
    return res;
}

void ManagedSql::prepareQuery() {
    if (!isConnected()) {
        throw sql::SQLException("Not connected to the database");
    }
}