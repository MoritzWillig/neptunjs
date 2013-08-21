/*
 * Author: Moritz Willig
 * Date:   21.8.2012
 * 
 * The OutputBuffer captures streams and handles nested buffer instances
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <cstring>

#include "outputBuffer.h"

using namespace std;

namespace OutputBuffer {

OutputBuffer::OutputBuffer() {
    this->buffer="";
}

OutputBuffer::~OutputBuffer() {
    this->buffer="";
}
    
string OutputBuffer::read() {
    return this->buffer;
}

void OutputBuffer::write(string s) {
    this->buffer+=s;
}

string OutputBuffer::flush() {
    string s=this->read();
    this->buffer="";
    return s;
}

void open() {
    OutputBuffer* b = new OutputBuffer();
    buffers.push_back(b);
}

string close() {
    OutputBuffer* b = buffers.back();
    buffers.pop_back();
    string s=b->flush();
    delete b;
    return s;
}

string closeAll() {
    string s="";
    while (buffers.size()!=0) {
        s+=close();
    }
    return s;
}

OutputBuffer* getCurrent() {
    if (buffers.empty()) { return NULL; }
    return buffers.back();
}

}