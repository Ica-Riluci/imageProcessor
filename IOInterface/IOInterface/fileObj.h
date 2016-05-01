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
    char* pushToBuffer();
    char* scratchData(int site, int len, char tar[]);
    int transToNum(int l, char source[]);
    /*
    fName        : the Name of the target file
    pushToBuffer : push data int to [buffer];
    scratchData  : scratch data in [tar[]\ at [site] by the length of [len]
    transDWORD   : transform a string, [source[]], into an integer*/

public :
    ifstream inFile;
    char* buffer;
    int fileLen;
    /*
    inFile  : the file dealing with input
    buffer  : the string to store the data
    fileLen : then length of the [buffer]
    */

public :
    const int byteSize = 8;
};

class BMPFiles:virtual public files
{

    /*
    This class supports the analysis of BMP files.
    */

public :
    BMPFiles(){}
    ~BMPFiles(){}
    BMPFiles(string fName);
    int constructBMPHeader();
    void constructRGBQUAD();
    void constructCIArray();
    int getBMType(char s[]);
    /*
    constructBMPHeader : construct the file header of BMP files
    constructRGBQUAD   : construct the RGBQUAD if there is
    constructCIArray   : construct the CIArray
    getBMPType         : get the type of the bitmap
    */


public :
    const int BM = 0;
    const int BA = 1;
    const int CI = 2;
    const int CP = 3;
    const int IC = 4;
    const int PT = 5;
	const int rDWORD = 4;
	const int typeSite = 1;
	const int sizeSite = 5;
	const int offsetSite = 13;
	const int infoSizeSite = 17;
	const int bitWidSite = 21;
	const int bitHeiSite = 25;
	const int planesSite = 29;
	const int bitsPPSite = 31;
	const int compressionSite = 33
	const int BMDataSizeSite = 37;
	const int hResSite = 41;
	const int vResSite = 45;
	const int colorsSite = 49;
	const int impColorsSite = 53;
    int BMType;
    int CIAStartSite, infoSize, BMDataSize;
	int BMSize, infoSize, bitWid, bitHei, planes, bitsPP, compression;
	int hRes, vRes, colors, impColors;
	char *rgbQUAD, *CIArray;
    /*
    BMType       : the type of the bitmap
    CIAStartSite : the start site of CIArray
    bitsPP       : bits per pixel
    */

};

#endif
