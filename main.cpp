#include<iostream>
#include<stdlib.h>

using namespace std;
int main() {

	cout << "hello world" << endl;
	ifstream infile;
	infile.open("qqzl.txt", ios::in);
	if (!infile.is_open())
	{
		cout << "��ȡ�ļ�ʧ��" << endl;
		return;
	}
	return 0;
}