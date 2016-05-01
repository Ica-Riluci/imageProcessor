#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <iostream>
#include <fstream>

class files
{
public :
	ifstream file;
	char *buffer;
	const int byteSize = 256;
	int len;

public :
	files(){}
	files(char fName[]);
	~files(){}

public :
	char* getData();
	char* getFileSegment(int start, int endp, char s[]);
	int getDWORD(char s[]);
	int getWORD(char s[]);
};

class bmpFiles:public files
{
public :
	bmpFiles(){}
	~bmpFiles(){}

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
	const int planesSite = 27;
	const int bitsPPSite = 29;
	const int compressionSite = 33
	const int BMDataSizeSite = 37;
	const int hResSite = 41;
	const int vResSite = 45;
	const int colorsSite = 49;
	const int impColorsSite = 53;
	int CIAStartSite;
	int BMType, BMSize, infoSize, bitWid, bitHei, planes, bitsPP, compression;
	int hRes, vRes, colors, impColors;
	char *rgbQUAD, *CIArray;

public :
	int constructFileHeader();
	int constructRGB();
	int getBMType(char s[]);
};
#endif
