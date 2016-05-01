#ifndef FILEOBJ_H
#define FILEOBJ_H

/*
This header describe the class of files. It consists of the basic class of file,
which can open, close and read and write a file, and a son class of it, BMPFiles,
which supports the analysis of the data of BMP files.
*/

#include <iostream>
#include <fstream>
#include <string>

class files
{

    /*
    This class supports opening and closing files. It can also scratch data from
    the files.
    */

public :
    files(){}
    ~files(){}
    files(string fName);
    char* pushToBuffer();
    char* scratchData(int site, int len, char tar[]);
    int transDWORD(char *source);
    int transWORD(char *source);
    /*
    fName        : the Name of the target file
    pushToBuffer : push data int to [buffer];
    scratchData  : scratch data in [tar[]\ at [site] by the length of [len]
    transDWORD   : transform a 4-character string, [source[]], into an integer
    transWORD    : transform a 2-character string, [source[]], into an integer*/

public :
    ifstream inFile;
    char* buffer;
    int fileLen;

public :
    const int byteSize = 256;
};

#endif