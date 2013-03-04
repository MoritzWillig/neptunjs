/* 
 * File:   main.cpp
 * Author: Moritz Willig
 *
 * Created on August 18, 2012, 3:32 AM
 */

#include "../libs/v8_64bit/include/v8.h"
#include <assert.h>
#include <algorithm>
#include <fcntl.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string.h>
#include <boost/array.hpp>

#include "addins.h"
#include "addins/outputBuffer/outputBuffer.h"
#include "Permission.h"
#include "internalObjects.h"
#include "abstractNative.h"

using namespace std;
//using namespace v8;

/**
 * Defines debugging output to be displayed
**/
//#define debugoutput
void debLog(string s, bool newline=true) {
#ifdef debugoutput
    std::cout<<s;
    if (newline) { std::cout<<endl; }
#endif
}

enum JSOutputMsg { OM_NO_ERROR=0, OM_EXEC_FILE=1, OM_NO_FILE=2, OM_INVALID_FLAG=3, OM_INVALID_PARAM=4, OM_JS_ERROR=5, OM_INVALID_LOGIN=6};

std::string formatOutput(JSOutputMsg statuscode, std::string output) {
    std::stringstream ios;
    
    std::string statusMsg="";
    switch (statuscode) {
        case OM_NO_ERROR:      statusMsg="OK"; break;
        case OM_EXEC_FILE:     statusMsg="No exec file given"; break;
        case OM_NO_FILE:       statusMsg="No file found"; break;
        case OM_INVALID_FLAG:  statusMsg="Unknown flag"; break;
        case OM_INVALID_PARAM: statusMsg="Invalid parameter"; break;
        case OM_JS_ERROR:      statusMsg="Uncaught JS Error"; break;
        case OM_INVALID_LOGIN: statusMsg="Invalid login"; break;
    }
    ios << statuscode << " " << statusMsg << "\nOUTPUT " << output.length() << "\n" << output <<"\n";
    return ios.str();
}

// Reads a file into a v8 string.
void ReadFile(const std::string name, char*& chars) {
  FILE* file = fopen(const_cast<char*>(name.c_str()), "rb");
  int size;
  if (file == NULL) {
      chars =new char[1];
      chars[0] = '\0';
      size=0;
      return;
  }
  
  fseek(file, 0, SEEK_END);
  size = ftell(file);
  rewind(file);
  
  chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = static_cast<int>(fread(&chars[i], 1, size - i, file));
    i += read;
  }
  fclose(file);
}

v8::Handle<v8::Value> parseJson(v8::Handle<v8::Value> jsonString) {
    v8::HandleScope scope;
    
    Handle<Context> context = Context::GetCurrent();
    Handle<Object> global = context->Global();

    Handle<Object> JSON = global->Get(String::New("JSON"))->ToObject();
    Handle<Function> JSON_parse = Handle<Function>::Cast(JSON->Get(String::New("parse")));

    return scope.Close(JSON_parse->Call(JSON, 1, &jsonString));
}


//typedef boost::array<string,2> array2s;
typedef vector<string> vectorns;
typedef vector<vectorns> vector2s;

vectorns split(string s, char delemiter, int limit=2) {    
    vectorns dest;

    int is=0; int i=s.find(delemiter,is); int ct=1;
    while ((i!=s.npos) and (ct<=limit)) {
        string pch=s.substr(is,i-is);
        if (pch.length()!=0) { dest.push_back(pch); }
        
        is=i+1;
        i=s.find(delemiter,is);
        ct++;
    }
    //split rest of string (last line without \n)
    string pch=s.substr(is,s.length());
    if (pch.length()!=0) { dest.push_back(pch); }
    
    return dest;
}

string IntToStr(int i) {
    ostringstream out;
    out << i;
    return out.str();
}


vector2s lineTokenize(string s, char delemiter, int limit=2) {
    vectorns lns=split(s,'\n', INT_MAX);
    vector2s dest;
    for (int i=0; i<lns.size(); i++) {
        if (lns[i].length()!=0) {
            dest.push_back(split(lns[i],delemiter,limit));
        }
    }
    
    return dest;
}

void upperCase(string& str) {
    for (unsigned int i=0;i<str.length();i++) {
        str[i]=toupper(str[i]);
    }
}

char* detag(char* str, const char* pre_repl, const char* app_repl) {
    std::vector<int> b; //begin
    std::vector<int> e; //end
    
    int bufferSize=strlen(str);
    int singleAdd=strlen(pre_repl)+strlen(app_repl);
    
    for (int i=0; i<strlen(str); i++) {
        if ((str[i+0]=='<') and (str[i+1]=='?') and (str[i+2]=='j') and (str[i+3]=='s')) {
            
            b.push_back(i);
            int j;
            for (j=i+4; j<strlen(str); j++) {
                if ((str[j+0]=='?') and (str[j+1]=='>')) {
                    break;
                }
            }
            e.push_back(j);
            i=j+2;
        }
        
        //qutotations, backslashes, tabs and new lines have to be encoded
        if ((str[i]=='\\' ) or (str[i]=='"' ) or (str[i]=='\t') or (str[i]=='\n') or (str[i]=='\r')) {
            bufferSize+=1;
        }
    }
    bufferSize+=singleAdd*(b.size()+1)-(b.size()*6);
    b.push_back(strlen(str));
    
    char* ret= new char[bufferSize+1];
    
    int c=0; //ret current char index
    int d=0; //str current char index
    
    //copy first string
    int firstStrEnd=(e.size()==0)?strlen(str):b[0];
    memcpy(&ret[c],&pre_repl[0],strlen(pre_repl)); c+=strlen(pre_repl);
    for (; d<firstStrEnd; d++) {
        switch (str[d]) {
                case '\\':
                case '"' : ret[c]='\\'; c++; ret[c]=str[d]; break;
                case '\t': ret[c]='\\'; c++; ret[c]='t'   ; break;
                case '\n': ret[c]='\\'; c++; ret[c]='n'   ; break;
                case '\r': ret[c]='\\'; c++; ret[c]='r'   ; break;
            default: ret[c]=str[d];
        }
        
        c++;
    } d+=4; //jump over "<?js"
    memcpy(&ret[c],&app_repl[0],strlen(app_repl)); c+=strlen(app_repl);
    
    for (int i=0; i<e.size(); i++) {
        //copy js code
        memcpy(&ret[c],&str[d],e[i]-(d));
        c+=e[i]-(d);
        d+=e[i]-(d)+2; //jump over "?>"
        
        //copy string code
        memcpy(&ret[c],&pre_repl[0],strlen(pre_repl)); c+=strlen(pre_repl);
        for (; d<b[i+1]; d++) {
            switch (str[d]) {
                    case '\\':
                    case '"' : ret[c]='\\'; c++; ret[c]=str[d]; break;
                    case '\t': ret[c]='\\'; c++; ret[c]='t'   ; break;
                    case '\n': ret[c]='\\'; c++; ret[c]='n'   ; break;
                    case '\r': ret[c]='\\'; c++; ret[c]='r'   ; break;
                default: ret[c]=str[d];
            }
            
            c++;
        } d+=4; //jump over "<?js"
        memcpy(&ret[c],&app_repl[0],strlen(app_repl)); c+=strlen(app_repl);
    }
    
    ret[bufferSize]=0;
    return ret;
}

PermissionCollection pc;
vector<string> loadedPermissions;
void loadPermission(string name) {
    debLog("Loading permission: "+name);                                            
    loadedPermissions.push_back(name);
    
    char* cs;
    ReadFile("./permissions/groups/"+name,cs);
    string s=cs; string c="";
    
    vector2s pms=lineTokenize(s,'|',5);
    for (int i=0; i<pms.size(); i++) {
        switch (pms[i][0][0]) {
            case 'a': //access: a|[rwx]|protocol[file/tcp/http]|lockTrace[true/false]|path
                {
                    Permission* pm = new Permission();
                    
                    pm->read   =(pms[i][1].find('r')!=pms[i][1].npos);
                    pm->write  =(pms[i][1].find('w')!=pms[i][1].npos);
                    pm->execute=(pms[i][1].find('x')!=pms[i][1].npos);
                    pm->protocol=pms[i][2];
                    upperCase(pms[i][3]);
                    pm->isFile  =(pms[i][3]=="TRUE");
                    pm->trace=(pms[i].size()==5)?pms[i][4]:"";
                    
                    pc.addPermission(pms[i][2],pm);
                }
                break;
            case 'g'://group: g|groupname
                { 
                    //check if not already added
                    if (find(loadedPermissions.begin(), loadedPermissions.end(), pms[i][1])==loadedPermissions.end()) {
                        loadPermission(pms[i][1]);
                    }
                }
                break;
        }
    }
    debLog("Loaded Permission "+name);
}

int main(int argc, char** argv, char** envp) {
    std::string execFile="";
    
    std::map<std::string, std::string> map;
    std::map<std::string, std::string> ::iterator mapi;
    
    debLog("<<MAPPING PARAMS<<");
    bool loggedIn=false; bool tagMode=false; bool cgiMode=false;
    for (int i=1; i<argc; i++) {
        std::string a=argv[i];
        if (a=="--help") {
            printf(" * NeptunJS 0.8.0 - server side JS implementation\n"
                   " * based on the JS V8 engine\n\n"
                   " * Copyright by Moritz Willig <moritz.willig@gmail.com>\n"
                   "neptunjs file [options]\n"
                   "file: js file to be executed\n"
                   "--help: show this help\n"
                   "-mname=jsonValue: object to be mapped into JS\n"
                   "-aname=pass: provides account login data"
                   "-t: enables tag mode [...<?js code ?>...]");
            return 0;
        }
        
        if (a=="-cgi") { cgiMode=true; } else {
            if (a[0]!='-') {
                execFile=a; //JS file
            } else { 
                a.erase(0,1); //delete "-"

                if (a.length()==0) {
                    formatOutput(OM_INVALID_PARAM,"Empty parameter"+i);
                    return 0;
                }

                int del;
                char v=a[0]; a.erase(0,1);
                switch (v) {
                    case 'm': //map data into js context
                              del=a.find("=");
                              map.insert(std::pair<std::string, std::string>(a.substr(0,del),a.substr(del+1,a.length())));
                              mapi=map.end(); --mapi; debLog(" * " + mapi->first + "=" + mapi->second);
                              break;
                    case 'a': //logindata
                              {
                                  vectorns acc= split(a,'=',2);
                                  debLog("Trying login as "+acc[0]+" : "+acc[1]);

                                  char* fl;
                                  ReadFile("./permissions/"+acc[0],fl);
                                  string flc=fl;
                                  vector2s lns=lineTokenize(flc,'|');

                                  for (int i=0; i<lns.size(); i++) {
                                      switch (lns[i][0][0]) {
                                          case 'p': if (lns[i][1]!=acc[1]) {
                                                            std::cout << formatOutput(OM_INVALID_LOGIN,"");   
                                                            return 0;
                                                        } else { loggedIn=true; }
                                                    break;
                                          case 'g': loadPermission(lns[i][1]);
                                                    break;
                                      }
                                  }
                              }
                              break;
                    case 't': tagMode=true;
                              break;
                    default : formatOutput(OM_INVALID_FLAG,"Invalid flag"+i);
                              return 0;
                }
            }
        }
    }
    if (!loggedIn) { std::cout << formatOutput(OM_INVALID_LOGIN,""); return 0; }
    debLog(">>MAPPING PARAMS>>");
    
    if (cgiMode) {
        char* efc=getenv("SCRIPT_FILENAME");
        if (efc!=NULL) {
            execFile.assign(efc);
        }
    }
    
    if (execFile=="") {
        std::cout << formatOutput(OM_EXEC_FILE,""); 
        return 0;
    }
    
    V8::Initialize(); //Create from snapshot or create new context
    HandleScope handle_scope; //Creates new handle scope -> new handles are stored here
    
    Persistent<Context> context = Context::New(); //creates new context (persistent->avoid deletion by the GC)
    Context::Scope context_scope(context); //all code will be executed in this scope
    
    debLog("<<LOADING ADDINS<<");
    addins::load(); //Load addins
    debLog(">>LOADED ADDINS>>");
    
    debLog("<<MAPPING PARAMETERS<<");
    //map given parameters to global scope
    for (mapi=map.begin(); mapi!=map.end(); mapi++) {
        TryCatch trycatch;
        Handle<Value> a=parseJson(String::New(mapi->second.c_str()));
        if (trycatch.HasCaught()) {
            String::AsciiValue ex_str(trycatch.Exception());
            std::cout << formatOutput(OM_INVALID_PARAM,*ex_str);
            return 0;
        }
        
        context->Global()->Set(String::New(mapi->first.c_str()),a);
        trycatch.~TryCatch();
    }
    
    //Mapping environment variables to "system.env"
    char** env;
    
    //get envp size   
    v8::Handle<v8::Object> sys=v8::Object::New();
    context->Global()->Set(String::New("system"),sys);
    v8::Handle<v8::Object> sysenv=v8::Object::New();
    sys->Set(String::New("env"),sysenv);
    
    int i=0;
    for (env=envp; *env!=0; env++) {
        char* cEnv=*env;
        char* cVl=strchr(cEnv,'=');
        cVl[0]=0; //split cEnv into 2 #0 terminated strings
        
        sysenv->Set(String::New(cEnv),String::New(++cVl));
        cVl--;
        cVl[0]='=';
        
        i++;
    }
    debLog(">>MAPPED PARAMETERS>>");
    
    debLog("<<INCLUDING PERMISSION<<");
    addin_permission::cppInit=true;
    //create global variable "permissions"
    Handle<Object> pmso=Object::New(); 
    context->Global()->Set(String::New("permissions"),pmso);

    //get permissions constructor
    
    
    Handle<Function> prmc = addin_permission::v8permission;
    //Handle<Function> prmc=Handle<Function>::Cast(addin_permission::v8permission);
    //cout<<v->IsNull()<<v->IsFunction()<<v->IsObject()<<"\n";

    //Handle<Function> prmc = Handle<Function>::Cast(addin_permission::v8permission->GetConstructor());
    //Handle<Object> o=Handle<Object>::Cast(context->Global()->Get(String::New("Permission")));
    //Handle<Function> prmc = Handle<Function>::Cast(o->GetConstructor());
    
    //manually create an permission object
    v8::Handle<v8::Function> an=addin_AbstractNative::v8abstractNative;
    Handle<Value> args[0]; Handle<Value> mpo=an->CallAsConstructor(0,args);
    InternalObject<Permission>* t=InternalObject<Permission>::castFrom(mpo,"permission",true);
    
    typedef std::map<string,PermissionSet*>::iterator pc_it;
    for (pc_it it=pc.perms.begin(); it!=pc.perms.end(); it++) {
        //add array to permissions object
        Handle<Array> pmsoa=Array::New(it->second->size());
        pmso->Set(String::New(it->first.c_str()),pmsoa);

        typedef vector<Permission*>::iterator ps_it;
        int i=0;
        for (ps_it its=it->second->begin(); its!=it->second->end(); its++) {
            //add mappedPermission to array
            Permission* p=*its;
            t->saveObj(p);
            
            //create mapped permission
            Handle<Value> args[1]; args[0]=mpo;
            Handle<Value> v=prmc->CallAsConstructor(1,args);
            //Handle<Value> v=prmc->NewInstance(1,args);
            
            pmsoa->Set(Number::New(i),v);
            
            i++;
        }
    }
    
    InternalObject<Permission>::releaseFrom(t);
    debLog(">>INCLUDED PERMISSION>>");
    
    
    debLog("<<COMPILING CODE<<");
    TryCatch trycatchc;
    char* schars; int size;
    ReadFile(execFile,schars);
    char* chars;
    if (tagMode) {
        chars=detag(schars,"outputBuffer.write(\"","\");");
        delete[] schars;
    } else { chars=schars; }
    
    if (cgiMode) {
        char* nl=strchr(chars,'\n');
        if (nl==NULL){
            schars="";
        } else {
            schars=nl+1;
        }
    } else { schars=chars; }
    Handle<String> source = String::New(schars);
    delete[] chars;
    
    Handle<Script> script = Script::Compile(source);
    if (trycatchc.HasCaught()) {
        ostringstream out;
        Handle<Value> exception = trycatchc.Exception(); 
        String::AsciiValue exception_str(exception);
        String::AsciiValue lnstr(trycatchc.Message()->GetSourceLine());
        out << "Line " << trycatchc.Message()->GetLineNumber() << ": ";
        out << *lnstr << "\n";
        out << *exception_str;
        std::cout << formatOutput(OM_JS_ERROR,out.str());
        return 0;
    }
    if (script.IsEmpty()) {
        std::cout << formatOutput(OM_NO_FILE,"");
        return 0;
    }
    trycatchc.~TryCatch();
    debLog(">>COMPILED CODE>>");
    
    debLog("<<STARTING SCRIPT<<");
    TryCatch trycatch;
    
    OutputBuffer::open();
    
    Handle<Value> result=script->Run();
    if (trycatch.HasCaught()) { //(result.IsEmpty()) { <-- from example code
        ostringstream out;
        Handle<Value> exception = trycatch.Exception(); 
        String::AsciiValue exception_str(exception);
        String::AsciiValue lnstr(trycatch.Message()->GetSourceLine());
        out << "Line " << trycatch.Message()->GetLineNumber() << ": ";
        out << *lnstr << "\n";
        out << *exception_str;
        std::cout << formatOutput(OM_JS_ERROR,out.str());
        return 0;
    }
    trycatch.~TryCatch();
    debLog(">>FINISHED SCRIPT<<");
    
    debLog("<<OUTPUT FORMAT<<");
    std::cout << formatOutput(OM_NO_ERROR,OutputBuffer::closeAll());   
    debLog(">>OUTPUT FORMAT>>");
    
    addins::unload(); //Unload addins
    context.Dispose(); //Deletes handle scope with all handles
    //on return from a "native" function use 'return handle_scope.Close(returnhandle);' to keep the value handle valid in the new scope
    
    return 0;
}