#include "fileObj.h"

using namespace std;

files::files(string fName)
{
    inFile.open(fName, ios_base::binary);
    buffer = pushToBuffer();
}

char* files::pushToBuffer()
{
    if (inFile)
    {
        inFile.seekg(0, inFile.end);
        int length = inFile.tellg();
        file.seekg(0, inFile.beg);
        char *result = new char[length];
        fileLen = length;
        file.read(result, length);
        file.close();
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
