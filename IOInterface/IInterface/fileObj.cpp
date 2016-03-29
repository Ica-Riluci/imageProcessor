#include "fileObj.h"
using namespace std;

files::files(char fName[])
{
	file.open(fName, ios_base::binary);
}

char* files::getData()
{
	if (file)
	{
		file.seekg(0, file.end);
		int length = file.tellg();
		file.seekg(0, file.beg);
		char *buff = new char[length];
		file.read(buff, length);
		file.close();
		return buff;
	}
}

char* files::getFileSegment(int start, int endp, char s[])
{
	char *r = new char[endp - start + 1];
	int i;
	for (i = start; i <= endp; ++i)
		r[i - start] = s[i];
	return r;
}

int bmpFiles::constructFileHeader()
{
	BMType = getBMType(files::getFileSegment(0, typeSite, buffer));
	if (BMType == -1)
		return 0;
	BMSize = getDWORD(files::getFileSegment(typeSite + 1, sizeSite, buffer));
	CIAStartSite = getDWORD(files::getFileSegment(sizeSite + rDWORD + 1, offsetSite, buffer));
	infoSize = getDWORD(files::getFileSegment(offsetSite + 1, infoSizeSite, buffer));
	bitWid = getDWORD(files::getFileSegment(infoSizeSite + 1, bitWidSite, buffer));
	bitHei = getDWORD(files::getFileSegment(bitWidSite + 1, bitHeiSite, buffer));
}

int bmpFiles::getBMType(char s[])
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

int bmpFiles::getDWORD(char s[])
{
	int l = 8;
	int base  = 1, i, r = 0;
	unsigned char x;
	for (i = 0; i < l; ++i)
	{
		x = s[i];
		r += x * base;
		base *= bitSize;
	}
	return r;
}