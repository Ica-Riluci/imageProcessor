#include "fileObj.h"

using namespace std;

char* files::pushToBuffer()
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
    buffer = pushToBuffer();
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
