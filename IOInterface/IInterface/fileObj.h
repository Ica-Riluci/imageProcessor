#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <iostream>
#include <fstream>

class files
{
public :
	ifstream file;
	char *buffer;

public :
	files(){}
	files(char fName[]);
	~files(){}

public :
	char* getData();
	char* getFileSegment(int start, int endp, char s[]);
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
	const int bitSize = 256;
	const int bitWidSite = 21;
	const int bitHeiSite = 25;
	int CIAStartSite;
	int BMType, BMSize, infoSize, bitWid, bitHei;
	char *bmpInfoHeader, *rgbQuad, *CIArray;

public :
	int constructFileHeader();
	int getBMType(char s[]);
	int getDWORD(char s[]);
};
#endif