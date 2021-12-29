#pragma once
#include<iostream>
#include"vertex.h"
#include<fstream>
#define MAX_CNT 100000

class MeshSimplification {
	//点集
	Vertex buffer[MAX_CNT];
	//现有面数
	int cntFace_N;
	//目标面数
	int cntFace_T;

public:
	MeshSimplification(void);
	~MeshSimplification(void);

	void readfile(const char s[100]);

};