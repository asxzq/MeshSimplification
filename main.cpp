#include<iostream>
#include<stdlib.h>
#include"meshSimplification.h"


using namespace std;
int main() {

	cout << "hello world" << endl;
	string pathNameOBJ = "F:\\code\\DS\\MeshSimplification\\data_basic1\\Utah_teapot_9438.obj";
	MeshSimplification *solution = new MeshSimplification();
	solution->fileRead(pathNameOBJ);
	return 0;
}