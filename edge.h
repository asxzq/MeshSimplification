#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"vec.h"

class Edge {
public:
	//边的序号
	int id;
	//边的顶点序号
	int v1, v2;
	//缩编后顶点
	Vec3d vPos;
	//代价
	double deltaValue;

	Edge(void);
	Edge(int _v1, int _v2) :v1(_v1), v2(_v2) {};
	Edge(int _id, int _v1, int _v2) :id(_id), v1(_v1), v2(_v2) {};
	~Edge(void);
};