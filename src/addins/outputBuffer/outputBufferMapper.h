/* 
 * File:   fileMapper.h
 * Author: moritz
 *
 * Created on September 17, 2012, 4:40 AM
 */

#ifndef OUTPUTBUFFERMAPPER_H
#define	OUTPUTBUFFERMAPPER_H

#include "../../mapper/macros.h"
#include "../../../libs/v8_64bit/include/v8.h"

using namespace v8;

namespace addin_outputBuffer {
    
namespace {

extern Persistent<Function> v8outputBuffer;

JS_METHOD(_open);
JS_METHOD(_close);

JS_METHOD(_write);
JS_METHOD(_read);
JS_METHOD(_flush);
}

void load();
void unload();
}

#endif	/* FILEMAPPER_H */

