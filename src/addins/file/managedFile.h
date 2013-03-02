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
#include "../basicAddin/BasicAddin.h"

using namespace std;

class ManagedFile : public BasicAddin {
public:
    ManagedFile(string folder="./");
    ~ManagedFile();
    
    bool setDirectory(string directory);
    string getDirectory();
    bool isInDirectory(string file);
    
    bool loadFile(string file);
    void closeFile();
    
    string getFileName(bool fullPath, bool cutDir);
    bool isLoaded();
    
    void setContent(string s);
    string getContent();
    
    string read(int pos, int length);
    void write(string s, int pos=-1);
    int getSize();
    
    void append(string s);
    
    static string absolutePath(string file);
private:
    string directory;
    bool loaded;
    string filename;
    FILE* fileHandle;
};

#endif	/* MANAGEDFILE_H */