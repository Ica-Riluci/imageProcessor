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
        len = length;
        file.read(result, length);
        file.close();
        return result;
    }
}

char* scratchData(int site, int len, char tar[])
{
    char *result = new char[len];
    for (int i = site; i < site + len; ++i)
        result[i - site] = tar[i];
    return result;
}
