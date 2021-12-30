#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"vec.h"

class Edge {
public:
	//�ߵ����
	int id;
	//�ߵĶ������
	int v1, v2;
	//����󶥵�
	Vec3d vPos;
	//����
	double deltaValue;

	Edge(void);
	Edge(int _v1, int _v2) :v1(_v1), v2(_v2) {};
	Edge(int _id, int _v1, int _v2) :id(_id), v1(_v1), v2(_v2) {};
	~Edge(void);
};