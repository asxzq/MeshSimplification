#pragma once
#include<iostream>
#include"vertex.h"
#include<fstream>
#include<string>
#define MAX_CNT 100000

class MeshSimplification {
	//�㼯
	Vertex vertexBuffer[MAX_CNT];
	//������
	int cntVertex;
	//����
	int cntEdge;
	//��������
	int cntFace_N;
	//Ŀ������
	int cntFace_T;

public:
	MeshSimplification(void);
	~MeshSimplification(void);

	void fileRead(std::string pathNameOBJ);

};