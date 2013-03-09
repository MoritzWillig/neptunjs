/* 
 * File:   main.cpp
 * Author: moritz
 *
 * Created on March 8, 2013, 10:19 PM
 */

#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "../../../src/comInterface/comunicationInterface.h"

using namespace std;

string getOrigin() {
    int bsz=255;
    int r=bsz;
    char* lnk=(char*)malloc(bsz+1);
    if (lnk==NULL) {
        formatOutput(OM_OUT_OF_MEM,"Function getOrigin");
        exit(EXIT_FAILURE);
    }
    r=readlink("/proc/self/exe",lnk,r);
    lnk[r]=0;
    
    char* c=strrchr(lnk,'/'); c[0]=0;
    
    string rs(lnk);
    
    free(lnk);
    return rs;    
}

/*
 * 
 */
int main(int argc, char** argv) {
    string execFile="";
    if (argc<2) {
        //read from environment variables
        char* efc=getenv("SCRIPT_FILENAME");
        if (efc!=NULL) {
            execFile.assign(efc);
        }
    } else {
        //read from command line arguments
        execFile=argv[2];
    }
    
    string exec=getOrigin()+"/neptunjs -cgi \""+execFile+"\" 2>&1";
    if (argc>1) {
        //pass arguments
        exec+=" "; exec+=argv[1];
    }
    
    FILE* pipe=popen(exec.c_str(),"r");
    if (!pipe) {
        cout<<formatOutput(OM_CANT_EXECUTE_NEPTUNJS,"");
        return 0;
    }
    const int BUFFER_SIZE=1024;
    char buffer[BUFFER_SIZE];
    string res="";
    while (!feof(pipe)) {
        if (fgets(buffer,BUFFER_SIZE,pipe)!=NULL) {
            res+=buffer;
        }
    }
    int stat=pclose(pipe);
    
    if (stat!=0) {
        cout<<formatOutput(OM_UNKNOWN_ERROR,res);
    } else { cout<<res; }
    return 0;
}

