/* 
 * File:   outputBuffer.h
 * Author: Moritz Willig
 *
 * Created on August 19, 2012, 6:39 AM
 */


#ifndef OUTPUTBUFFER_H
#define	OUTPUTBUFFER_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

namespace OutputBuffer {
        
class OutputBuffer {
public:
    OutputBuffer();
    ~OutputBuffer();
    
    string read();
    void write(string s);
    string flush();
            
private:
    string buffer;
};

namespace { list<OutputBuffer*> buffers; }

void open();
string close();
string closeAll();
OutputBuffer* getCurrent();

}

#endif