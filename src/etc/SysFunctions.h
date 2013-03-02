/* 
 * File:   SysFunctions.h
 * Author: moritz
 *
 * Created on February 16, 2013, 10:51 PM
 */

#ifndef SYSFUNCTIONS_H
#define	SYSFUNCTIONS_H

#include <string>
#include <vector>
using namespace std;


namespace SysFunctions {
    namespace {
        class SysFunctionsInit {
        public:
            SysFunctionsInit();
            ~SysFunctionsInit();
        };
        extern SysFunctionsInit inFnObj;
    }
    
    string resolvePath(const string& path, const vector<string>& cwd);
    
    void explode(const string& s, const char& delemiter, vector<string>& p);
    string implode(const vector<string>& elements, const string& delimiter);
      
    extern vector<string>* cwd;
};

#endif	/* SYSFUNCTIONS_H */

