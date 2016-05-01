#include "fileObj.h"

char* files::popToBuffer()
{
    if (inFile)
    {
        inFile.seekg(0, inFile.end);
        int length = inFile.tellg();
        inFile.seekg(0, inFile.beg);
        char *result = new char[length];
        fileLen = length;
        inFile.read(result, length);
        inFile.close();
        return result;
    }
}

char* files::scratchData(int site, int len, char tar[])
{
    char *result = new char[len];
    for (int i = site; i < site + len; ++i)
        result[i - site] = tar[i];
    return result;
}

int files::transToNum(int l, char source[])
{
    int result = 0;
    for (int i = 0; i < l; ++i)
        result += source[i] * (1 << (i * byteSize));
    return result;
}

BMPFiles::BMPFiles(string fName)
{
    inFile.open(fName, ios_base::binary);
    buffer = popToBuffer();
    constructBMPHeader();
    if (bitsPP <= 8)
        constructRGBQUAD();
    constructCIArray();
}

int BMPFiles::constructBMPHeader()
{
    BMType = getBMType(scratchData(0, typeSite + 1, buffer));
    if (BMType == -1)
        return 0;
    BMSize = transToNum(4, scratchData(typeSite + 1, sizeSite - typeSite, buffer));
    CIAStartSite = transToNum(4, scratchData(sizeSite + rDWORD + 1, offsetSite - sizeSite - rDWORD, buffer));
    infoSize = transToNum(4, scratchData(offsetSite + 1, infoSizeSite - offsetSite, buffer));
    bitWid = transToNum(4, scratchData(infoSizeSite + 1, bitWidSite - infoSizeSite, buffer));
    bitHei = transToNum(4, scratchData(bitWidSite + 1, bitHeiSite - bitWidSite, buffer));
    planes = transToNum(4, scratchData(bitHeiSite + 1, planesSite - bitHeiSite, buffer));
    bitsPP = transToNum(2, scratchData(planesSite + 1, bitsPPSite - planesSite, buffer));
    compression = transToNum(4, scratchData(bitsPPSite + 1, compressionSite - bitsPPSite, buffer));
    BMDataSize = transToNum(4, scratchData(compressionSite + 1, BMDataSizeSite - compressionSite, buffer));
    hRes = transToNum(4, scratchData(BMDataSizeSite + 1, hResSite - BMDataSizeSite, buffer));
    vRes = transToNum(4, scratchData(hResSite + 1, vResSite - hResSite, buffer));
    colors = transToNum(4, scratchData(vResSite + 1, colorsSite - vResSite, buffer));
    impColors = transToNum(4, scratchData(colorsSite + 1, impColorsSite - colorsSite, buffer));
}

void BMPFiles::constructRGBQUAD()
{
    rgbQUAD = scratchData(impColorsSite + 1, CIAStartSite - impColorsSite - 1, buffer);
}

void BMPFiles::constructCIArray()
{
    CIArray = scratchData(CIAStartSite, fileLen - CIAStartSite + 1, buffer);
}

int BMPFiles::getBMType(char s[])
{
	if (s[0] == 'B')
	{
		if (s[1] == 'M')
			return BM;
		else if (s[1] == 'A')
			return BA;
		else
			return -1;
	}
	else if (s[0] == 'C')
	{
		if (s[1] == 'I')
			return CI;
		else if (s[1] = 'P')
			return CP;
		else
			return -1;
	}
	else if (s[0] == 'I')
	{
		if (s[1] == 'C' )
			return IC;
		else
			return -1;
	}
	else if (s[0] == 'P')
	{
		if (s[1] == 'T')
			return PT;
		else
			return -1;
	}
	return -1;
}

inline void pushToFile(string source)
{
    outFile << source;
}

void BMPFiles::outp24Bit(string fName)
{
    outFile.open(fName, ios_base::binary);
    outpHeader();
}

void BMPFiles::outpHeader()
{
    pushToFile("BM");
    pushToFile(transToString(4, impColorsSite + 1 + sizeOfBody(bitsPP)));
    for (int i = 0; i < 4; ++i)
        pushToFile((string)((char)0));
    pushToFile(transToString(4, CIAStartSite));
    pushToFile(transToString(4, infoSize));
    pushToFile(transToString(4, bitWid));
    pushToFile(transToString(4, bitHei));
    pushToFile(transToString(2, 1));
    pushToFile(transToString(2, bitsPP));
    pushToFile(transToString(4, compression));
    pushToFile(transToString(4, BMDataSize));
    pushToFile(transToString(4, hRes));
    pushToFile(transToString(4, vRes));
    pushToFile(transToString(4, colors));
    pushToFile(transToString(4, impColors));
}

string files::transToString(int l, int source)
{
    string result = "";
    for (int i = 0; i < l; ++i)
    {
        result += (string)((char)(source % (1 << byteSize)));
        source /= 1 << byteSize;
    }
    return result;
}

inline int BMPFiles::sizeOfBody(int bpp)
{
    return (sizeOfRGBQUAD(bpp) + sizeOfCIArray(bpp, bitWid, bitHei));
}

inline int BMPFiles::sizeofRGBQUAD(int bpp)
{
    switch (bpp)
    {
    case 1 :
        return 8;
        break;
    case 4 :
        return 64;
        break;
    case 8 :
        return 1024;
        break;
    case 16 :
    case 24 :
        return 0;
        break;
    default :
        break;
    }
}

inline int BMPFiles::sizeofCIArray(int bpp, int wid, int hei)
{
    switch (bpp)
    {
    case 4 :
        int c = wid / 8;
        if (wid % 8 > 0)
            ++c;
        return (hei * c * 4);
        break;
    case 8 :
        return (hei * wid);
        break;
    case 16 :
    case 24 :
        return (hei * wid * 3);
        break;
    }
}
