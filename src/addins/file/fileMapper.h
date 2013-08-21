/* 
 * File:   fileMapper.h
 * Author: moritz
 *
 * Created on September 17, 2012, 4:40 AM
 */

#ifndef FILEMAPPER_H
#define	FILEMAPPER_H

#include "../../mapper/macros.h"
#include "../../../libs/v8_64bit/include/v8.h"

using namespace v8;

namespace addin_file {
    
namespace {

extern Persistent<Function> v8file;

JS_METHOD(_constructor);
JS_GETTER(_getFileName); 
JS_METHOD(_loadFile);


JS_METHOD(_isInDirectory);

JS_METHOD(_loadFile);
JS_METHOD(_closeFile);

JS_METHOD(_getFileName); //string ([bool])
JS_METHOD(_isLoaded);

JS_METHOD(_setContent);
JS_METHOD(_getContent);

JS_METHOD(_read);
JS_METHOD(_write);
JS_METHOD(_getSize);

JS_METHOD(_append);
}

void load();
void unload();
}

#endif	/* FILEMAPPER_H */

