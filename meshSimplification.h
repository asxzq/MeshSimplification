#pragma once
#include<iostream>
#include"vertex.h"
#include<fstream>
#define MAX_CNT 100000

class MeshSimplification {
	//�㼯
	Vertex buffer[MAX_CNT];
	//��������
	int cntFace_N;
	//Ŀ������
	int cntFace_T;

public:
	MeshSimplification(void);
	~MeshSimplification(void);

	void readfile(const char s[100]);

};