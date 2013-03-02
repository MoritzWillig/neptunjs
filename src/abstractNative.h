/* 
 * File:   abstractNative.h
 * Author: moritz
 *
 * Created on January 27, 2013, 11:17 PM
 */

#ifndef ABSTRACTNATIVE_H
#define	ABSTRACTNATIVE_H

#include <iostream>
#include "mapper/macros.h"
#include "../../../libs/v8/include/v8.h"

namespace addin_AbstractNative {
    extern v8::Persistent<v8::Function> v8abstractNative;
    
namespace {
JS_METHOD(_constructor);
}

void load();
void unload();
}

#endif	/* ABSTRACTNATIVE_H */
