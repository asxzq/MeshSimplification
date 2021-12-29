#include<iostream>
#include<stdlib.h>

using namespace std;
int main() {

	cout << "hello world" << endl;
	ifstream infile;
	infile.open("qqzl.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "¶ÁÈ¡ÎÄ¼þÊ§°Ü" << endl;
		return;
	}
	return 0;
}