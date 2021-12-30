#include<iostream>
#include<stdlib.h>
#include"meshSimplification.h"
#include <time.h>

using namespace std;
int main() {

	cout << "hello world" << endl;

	string pathNameOBJ1 = "F:\\code\\DS\\MeshSimplification\\data\\data_basic2\\serapis_88040.obj";
	string pathNameOBJ2 = "F:\\code\\DS\\MeshSimplification\\result\\data_basic2\\serapis_88040.obj";
	string pathNameOBJ3 = "F:\\code\\DS\\MeshSimplification\\result\\data_basic2\\serapis_88040.obj_true.obj";

	MeshSimplification *solution = new MeshSimplification();
	solution->fileRead(pathNameOBJ1);
	solution->fileWrite(pathNameOBJ3);
	clock_t start = clock();
	solution->edgeCollapse(10000);
	clock_t finish = clock();
	solution->fileWrite(pathNameOBJ2);

	cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}