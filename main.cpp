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

	//string inFold = "F:\\code\\DS\\MeshSimplification\\data\\data_advanced1\\tortuga_152728.obj";
	string inFold = "F:\\code\\DS\\MeshSimplification\\data\\data_basic1\\Utah_teapot_9438.obj";
	//string outFold = "F:\\code\\DS\\MeshSimplification\\result\\data_advanced1\\tortuga_152728.obj";
	string outFold = "F:\\code\\DS\\MeshSimplification\\result\\data_basic1\\Utah_teapot_9438.obj";



	MeshSimplification *solution = new MeshSimplification();
	solution->fileRead(inFold);
	clock_t start = clock();
	solution->edgeCollapse(10000);
	clock_t finish = clock();
	solution->fileWrite(outFold);

	cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}