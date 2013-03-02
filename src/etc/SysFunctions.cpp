/* 
 * File:   SysFunctions.cpp
 * Author: moritz
 * 
 * Created on February 16, 2013, 10:52 PM
 */

#include "SysFunctions.h"
#include <vector>
#include <iostream>

namespace SysFunctions {

    namespace {
        SysFunctionsInit::SysFunctionsInit() {
            SysFunctions::cwd=new vector<string>();
            SysFunctions::cwd->push_back("test");
        }
        SysFunctionsInit::~SysFunctionsInit() {
            delete SysFunctions::cwd;
        }
        SysFunctionsInit inFnObj;
    }
    
    string resolvePath(const string& path, const vector<string>& cwd) {
        vector<string> p;
        vector<string> r;
        explode(path,'/',p);
        
        if ((p[0]==".") or (p[0]=="..")) {
            r.insert(r.end(),cwd.begin(),cwd.end());
        }
        if (p[0]=="..") { r.pop_back(); }
        
        for (int i=1; i<p.size(); i++) {
            if ((p[i]=="") or (p[i]==".")) { continue; }
            if (p[i]=="..") {
                if (p.size()!=0) {
                    r.pop_back();
                } else {
                    break;
                }
            } else {
                r.push_back(p[i]);
            }
        }
        
        return "/"+implode(r,"/");
    }

    void explode(const string& s, const char& delemiter, vector<string>& p) {    
        int is=0; int i=s.find(delemiter,is); int ct=1;
        while (i!=s.npos) {
            p.push_back(s.substr(is,i-is));
            
            is=i+1;
            i=s.find(delemiter,is);
            ct++;
        }
        p.push_back(s.substr(is,s.length()));
    }
    
    string implode(const vector<string>& elements, const string& delimiter) {
        string result="";
        if (elements.size()!=0) { result+=elements[0]; }
        for (int i=1; i<elements.size(); i++) {
                result+=(delimiter+elements[i]);
        }
        return result;
    }
    
    vector<string>* cwd;
    
}

