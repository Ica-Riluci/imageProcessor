#include <iostream>
#include <fstream>
#include <iomanip>
#include <bitset>
using namespace std;

int main () {
	char s[256] = {0};

	ifstream inp("red.bmp", ios_base::binary);

	inp.read(s, 256);

	int x,i;
	for (i = 0; i < 256; ++i)
	{
		x = s[i];
		cout << bitset<8>(x);
	}
	system("pause");
	return 0;
}
