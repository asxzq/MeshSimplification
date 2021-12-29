#pragma once
#include<iostream>
#include"vertex.h"
#include<fstream>
#include<string>
#define MAX_CNT 100000

class MeshSimplification {
	//点集
	Vertex vertexBuffer[MAX_CNT];
	//顶点数
	int cntVertex;
	//边数
	int cntEdge;
	//现有面数
	int cntFace_N;
	//目标面数
	int cntFace_T;

public:
	MeshSimplification(void);
	~MeshSimplification(void);

	void fileRead(std::string pathNameOBJ);

};