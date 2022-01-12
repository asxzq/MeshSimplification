#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"vec.h"

#define MAX_VALUE 9999999;

class Edge {
public:
	//边的序号
	int id;
	//边的顶点序号
	int v1, v2;
	//缩边后顶点
	Vec3d vPos;
	//缩边代价,新点到原来两点所有所在面的距离
	double deltaValue;

	Edge(void);
	Edge(int _v1, int _v2);
	Edge(int _id, int _v1, int _v2);
	~Edge(void);
};