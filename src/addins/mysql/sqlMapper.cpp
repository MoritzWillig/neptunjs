/* 
 * File:   fileMapper.cpp
 * Author: Moritz Willig
 * 
 * Created on September 17, 2012, 2:17 AM
 */

#include <iostream>
#include <sstream>

#include "../../../libs/v8/include/v8.h"
#include "../../mapper/macros.h"
#include "../../internalObjects.h"
#include "../../mapper/PermissionChecks.h"
#include "managedSql.h"
#include "sqlMapper.h"


using namespace v8;

namespace addin_sql {

namespace {

Persistent<Function> v8sql;

JS_METHOD(sqlConstructor) {    
    if (!args.IsConstructCall()) {
        return ThrowException(String::New("Cannot call constructor as function"));
    }
    
    InternalObject<ManagedSql>* t=InternalObject<ManagedSql>::castFrom(args.This(),"managedsql",true);
    ManagedSql *pSql = new ManagedSql();
    t->saveObj(pSql);
    
    //save default permission array
    if (args.Length()>0) {
        args.This()->Set(String::New("permissions"),args[0]);
    } else {
        v8::Handle<v8::Value> p=v8::Context::GetCurrent()->Global()->Get(v8::String::New("permissions"));
        if (p->IsObject()) {
            v8::Handle<v8::Object> o=v8::Handle<v8::Object>::Cast(p);
            v8::Handle<v8::Value> a=o->Get(String::New("sql"));
            if (!a->IsUndefined()) {
                args.This()->Set(String::New("permissions"),a);
            }
        }
    }
    
    return args.This();
}

JS_METHOD(sqlDestructor) {
    InternalObject<ManagedSql>* t=InternalObject<ManagedSql>::castFrom(args.This(),"managedsql",true);
    delete t->getObj();
    
    InternalObject<ManagedSql>::releaseFrom(t);
}

JS_METHOD(sqlConnect) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    if (args.Length()!=3) { return ThrowException(String::New("False parameter count")); }
    
    string s=*String::Utf8Value(args[0]);
    
    Permission* p=PermissionChecks::canAccept<Permission>(args.This()->Get(v8::String::New("permissions")),s);
    if (p==NULL) {
        return ThrowException(Exception::Error(String::New("No Permissions were given for the requested action")));
    }
    pSql->importFromPermission(*p);
    
    try {try {
        pSql->connect(
                s, //adress
                *String::Utf8Value(args[1]), //name
                *String::Utf8Value(args[2])  //password
         );
    } catch (sql::SQLException &e) {
        stringstream ss;
        ss<<"SQL Error: "<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<endl<<
            e.what()<<":"<<
            e.getErrorCode()<<">"<<
            e.getSQLState().c_str()<<endl;
        string sx=ss.str();
        return ThrowException(String::New(
                sx.c_str()
        ));
    }} catch(...) {
        return ThrowException(String::New(
                "SQL Error: Unknown exception"
        ));
    }
}

JS_METHOD(sqlClose) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    pSql->clearRights();
    return v8::Boolean::New(pSql->close());
}

JS_METHOD(sqlIsCreated) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    return v8::Boolean::New(pSql->isCreated());    
}

JS_METHOD(sqlIsConnected) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    return v8::Boolean::New(pSql->isConnected());

}

JS_METHOD(sqlGetCommand) {
    if (args.Length()!=0) { return ThrowException(String::New("False parameter count")); }
    
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    return v8::String::New(pSql->getCommand().c_str());
}

JS_METHOD(sqlSetCommand) {
    if (args.Length()!=1) { return ThrowException(String::New("False parameter count")); }
    
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    
    pSql->setCommand(*String::Utf8Value(args[0]));
    return v8::Undefined();
}

JS_METHOD(sqlQuery) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    bool single=false; string s="";
    switch (args.Length()) {
        case 0: break;
        case 1: pSql->setCommand(*String::Utf8Value(args[0])); break;
        case 2:
            s=*String::Utf8Value(args[1]);
            if (s=="line") {
                pSql->setCommand(pSql->getCommand()+" LIMIT 1");
            } else {
                if (s=="single") {
                    single=true;
                    pSql->setCommand(pSql->getCommand()+" LIMIT 1");
                } else {
                    if (s!="all") { return ThrowException(String::New("SQL: Unknown value. Accepted: 'all'|'line'|'single'")); }
                }
            }
            break;
        default:
            return ThrowException(String::New("SQL: Too many parameters"));
    }
    
    try {try {
        pSql->executeQuery();
        sql::ResultSet* res=pSql->getLastResult();
        sql::ResultSetMetaData* rsmd=res->getMetaData();
        
        if (!single) {
            return addin_sql::mapResult(rsmd, res);
        } else {
            res->beforeFirst();
            if (!res->next()) { return v8::Undefined(); }
            
            string s=rsmd->getColumnTypeName(1);
            if (s=="BOOLEAN") {
                    return v8::Boolean::New(res->getBoolean(1));
            } else { if (s=="STRING") {
                string st=res->getString(1);    
                return v8::String::New(st.c_str());
            } else { if (s=="INT") {
                    return v8::Integer::New(res->getInt(1));
            //} else { if (s=="CONCURRENCY") {  
            //        return v8::Integer::New(static_cast<int>(res->getConcurrency(0)));
            } else { if (s=="UINT") { 
                    return v8::Integer::NewFromUnsigned(res->getUInt(1));
            } else { if (s=="DOUBLE") { 
                    return v8::Number::New(res->getDouble(1));
            } else {
                    return v8::ThrowException(v8::Exception::Error(v8::String::New("Unknown datatype")));
            }}}}}//}
        }
    } catch (sql::SQLException &e) {
        stringstream ss;
        ss<<"SQL Error: "<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<endl<<
            e.what()<<":"<<
            e.getErrorCode()<<">"<<
            e.getSQLState().c_str()<<endl;
        string sx=ss.str();
        return ThrowException(String::New(
                sx.c_str()
        ));
    }} catch(...) {
        return ThrowException(String::New(
                "SQL Error: Unknown exception"
        ));
    }
}

JS_METHOD(sqlExecute) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();
    if (args.Length()==1) {
        pSql->setCommand(*String::Utf8Value(args[0]));
    } else {
        if (args.Length()!=0) {
                return ThrowException(String::New("SQL: Too many parameters"));
        }
    }
    
    try {try {
        return v8::Boolean::New(pSql->execute());
    } catch (sql::SQLException &e) {
        stringstream ss;
        ss<<"SQL Error: "<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<endl<<
            e.what()<<":"<<
            e.getErrorCode()<<">"<<
            e.getSQLState().c_str()<<endl;
        string sx=ss.str();
        return ThrowException(String::New(
                sx.c_str()
        ));
    }} catch(...) {
        return ThrowException(String::New(
                "SQL Error: Unknown exception"
        ));
    }    
}

JS_METHOD(sqlUpdate) {
    ManagedSql* pSql=InternalObject<ManagedSql>::trustedGet(args.Holder())->getObj();

    if (args.Length()==1) {
        pSql->setCommand(*String::Utf8Value(args[0]));
    } else {
        if (args.Length()!=0) {
                return ThrowException(String::New("SQL: Too many parameters"));
        }
    }
    
    try {try {
        return v8::Integer::New(pSql->executeUpdate());
    } catch (sql::SQLException &e) {
        stringstream ss;
        ss<<"SQL Error: "<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<endl<<
            e.what()<<":"<<
            e.getErrorCode()<<">"<<
            e.getSQLState().c_str()<<endl;
        string sx=ss.str();
        return ThrowException(String::New(
                sx.c_str()
        ));
    }} catch(...) {
        return ThrowException(String::New(
                "SQL Error: Unknown exception"
        ));
    }        
}

v8::Handle<v8::Array> mapResult(sql::ResultSetMetaData* meta, sql::ResultSet* res) {
    v8::HandleScope hs;
    
    v8::Local<v8::Array> ress = v8::Array::New(res->rowsCount()); //create resultset
    res->beforeFirst();
    for (int x=0; res->next(); x++) {
        
        v8::Handle<v8::Array> arr = v8::Array::New(meta->getColumnCount());
        ress->Set(x,arr); //map line into array
        
        for (unsigned int i=1; i<=meta->getColumnCount(); i++) { //for each cell
            //res->getInt64() int64
            //res->getUInt64() uint64
            string s=meta->getColumnTypeName(i);
                //case "BLOB"         :
                //    arr->Set(i-1,v8::Data::New());
            if (s=="BOOLEAN") {
                    arr->Set(i-1,v8::Boolean::New(res->getBoolean(i)));
            } else { if (s=="VARCHAR") {
                    arr->Set(i-1,v8::String::New(res->getString(i).c_str()));
            } else { if (s=="INT") {
                    arr->Set(i-1,v8::Integer::New(res->getInt(i)));
                //case "CONCURRENCY"  :
                //    arr->Set(i-1,v8::Integer::New(res->getConcurrency(i)));
            } else { if (s=="UINT") {
                    arr->Set(i-1,v8::Integer::NewFromUnsigned(res->getUInt(i)));
            } else { if (s=="DOUBLE") {
                    arr->Set(i-1,v8::Number::New(res->getDouble(i)));
            } else {
                string sx="[Unknown "+s+"]";
                arr->Set(i,v8::String::New(sx.c_str()));
            }}}}}
        }
    }
    return hs.Close(ress);
}

} //End namespace

/*
 * Mapps the ManagedFile class as "File" into the JS-Context
 */
void load() {
    HandleScope hs;
    
    //Create new class template
    Handle<FunctionTemplate> sql_templ = FunctionTemplate::New(sqlConstructor);
    sql_templ->SetClassName(String::New("SQL")); //set template name
    
    //get instance template; create space for native class pointer
    Handle<ObjectTemplate> it = sql_templ->InstanceTemplate();
    it->SetInternalFieldCount(1); /* managedFile */
    
    
    //instance vars (File.*)
    //file_templ->Set("loadFile",FunctionTemplate::New(fileLoadFile));
 
    //add prototype functions (new File.*)
    Local<ObjectTemplate> sql_proto = sql_templ->PrototypeTemplate();
    
    v8::Handle<v8::Signature> sign=v8::Signature::New(sql_templ);
    SET_NATIVE(sql_proto,"connect",sqlConnect,sign);
    SET_NATIVE(sql_proto,"close",sqlClose,sign);
    SET_NATIVE(sql_proto,"isCreated",sqlIsCreated,sign);
    SET_NATIVE(sql_proto,"isConnected",sqlIsConnected,sign);
    SET_NATIVE(sql_proto,"setCommand",sqlSetCommand,sign);
    SET_NATIVE(sql_proto,"getCommand",sqlGetCommand,sign);
    SET_NATIVE(sql_proto,"query",sqlQuery,sign);//[[n],[n]] ([string],["all"|"line"|"single"])
    SET_NATIVE(sql_proto,"execute",sqlExecute,sign);//bool ([string])
    SET_NATIVE(sql_proto,"update",sqlUpdate,sign);//int ([string])
    
    v8::Context::GetCurrent()->Global()->Set(String::New("SQL"),sql_templ->GetFunction()); //map file into global object
    v8sql = Persistent<Function>::New(sql_templ->GetFunction());
}

void unload() {
    v8sql.MakeWeak(NULL,NULL);
}

}