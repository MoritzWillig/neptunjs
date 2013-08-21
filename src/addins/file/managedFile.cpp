/*
 * Author: Moritz Willig
 * Date:   21.8.2012
 * 
 * Managed File which allow modifing files in a specified folder, but prevents
 * operations outside of the given folder.
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <cstring>

#include "../../etc/SysFunctions.h"
#include "managedFile.h"

using namespace std;

ManagedFile::ManagedFile(string folder) {
    setDirectory(folder);
    loaded=false;
    filename="";
    fileHandle=NULL;
}

ManagedFile::~ManagedFile() {
    setDirectory("");
    closeFile();
    cout<<"managed file: destructor call\n";
}
    
bool ManagedFile::setDirectory(string directory) {
    this->directory=this->absolutePath(directory);
}

string ManagedFile::getDirectory() {
    return directory;
}
    
bool ManagedFile::loadFile(string file) {
    if (isLoaded()) { closeFile(); }
    if (!isInDirectory(file)) { return false; }
    
    fileHandle = fopen(const_cast<char*>(file.c_str()), "r+");
    if (fileHandle!=NULL) { filename=file; loaded=true; }
    
    return isLoaded();
}

void ManagedFile::closeFile() {
    filename="";
    loaded=false;
    
    if (!isLoaded()) { return; }
    fclose(fileHandle);
}
    
string ManagedFile::getFileName(bool fullPath, bool cutDir) {
    if (!isLoaded()) {return ""; }
    if (fullPath) {
        string s=absolutePath(filename);
        if (cutDir==false) {
            return s;
        } else {
            string sx=s.substr(directory.length(),s.length());
            return sx;
        }
    } else {
        return filename;
    }
}

bool ManagedFile::isLoaded() {
    return loaded;
}
    
void ManagedFile::setContent(string s) {
    if (!isLoaded()) { return; }
    
    fileHandle=freopen(const_cast<char*>(filename.c_str()),"w+",fileHandle);
    if (fileHandle==NULL) { closeFile(); return; }
    
    append(s);
}

string ManagedFile::getContent() {
    if (!isLoaded()) { return ""; }
    
    return read(0,getSize());
}
    
string ManagedFile::read(int pos, int length) {
    if (!isLoaded()) { return ""; }
    
    int r=fseek(fileHandle,pos,SEEK_SET);
    if (r!=0) { closeFile(); return ""; }
    
    char* res;
    res = new char[length+1];
    res[length]='\0';
    for (int i = 0; i < length;) {
        int read = static_cast<int>(fread(&res[i], 1, length-i, fileHandle));
        i += read;
        if (read==0) { break; }
    }
    
    return res;
}

void ManagedFile::write(string s, int pos) {
    if (!isLoaded()) { return; }
    
    int r=fseek(fileHandle,pos,SEEK_SET);
    if (r!=0) { closeFile(); return; }
    
    r=fwrite(const_cast<char*>(s.c_str()),1,s.length(), fileHandle);
    if (r!=s.length()) { closeFile(); return; }
}

int ManagedFile::getSize() {
  if (!isLoaded()) { return -1; }
  
  fseek(fileHandle, 0, SEEK_END);
  return ftell(fileHandle);
}

void ManagedFile::append(string s) {
    if (!isLoaded()) { return; }
    
    fputs(s.c_str(),fileHandle);
}
    
bool ManagedFile::isInDirectory(string file) {
    return (absolutePath(file).substr(0,directory.length())==directory);
}

string ManagedFile::absolutePath(string file) {
    return SysFunctions::resolvePath(file,*SysFunctions::cwd);
    /*
    char* symPath = const_cast<char*>(file.c_str());
    char* rp; string s;
    
    try {
        char *rp=realpath(symPath,NULL);
        
        if (rp!=NULL) {
            s=rp;
            free(rp);
        } else { s=""; }
    } catch(...) {
        s="";
    }
    
    return s;
    */
}