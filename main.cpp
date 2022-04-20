#include<iostream>
#include<stdlib.h>
#include"meshSimplification.h"
#include <time.h>

using namespace std;
int main() {

	cout << "hello world" << endl;

	string pathNameOBJ1 = "E:\Code\C++_VS\MashSimplification\MashSimplification";
	string pathNameOBJ2 = "F:\\code\\DS\\MeshSimplification\\result\\data_basic2\\serapis_88040.obj";
	string pathNameOBJ3 = "F:\\code\\DS\\MeshSimplification\\result\\data_basic2\\serapis_88040.obj_true.obj";

	//string inFold = "F:\\code\\DS\\MeshSimplification\\data\\data_advanced1\\tortuga_152728.obj";
	string inFold = "E:\\Code\\C++_VS\\MashSimplification\\MashSimplification\\data\\angel.obj";
	//string outFold = "F:\\code\\DS\\MeshSimplification\\result\\data_advanced1\\tortuga_152728.obj";
	string outFold = "E:\\Code\\C++_VS\\MashSimplification\\MashSimplification\\result\\angel.obj";



	MeshSimplification *solution = new MeshSimplification();
	clock_t start = clock();
	solution->fileRead(inFold);
	
	
	//basic2 & advanved1
	solution->edgeCollapse(1000);
	//basic1
	//solution->edgeCollapseSingle(1923, 3641);
	
	clock_t finish = clock();
	solution->fileWrite(outFold);

	cout << "# time use: " << (double)(finish - start) / CLOCKS_PER_SEC << " s" << endl;
	return 0;
}