/* 
 * File:   script.h
 * Author: moritz
 *
 * Created on October 20, 2012, 5:03 AM
 */

#ifndef SCRIPT_H
#define	SCRIPT_H

#include <string>
#include "../../v8/include/v8.h"

using namespace std;

class script {
public:
    script();
    ~script();
    
    void load(string s);
    v8::Handle<v8::Value> run();
    
private:

};

#endif	/* SCRIPT_H */

