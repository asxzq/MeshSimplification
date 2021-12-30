#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"vec.h"

#define MAX_VALUE 9999999;

class Edge {
public:
	//�ߵ����
	int id;
	//�ߵĶ������
	int v1, v2;
	//���ߺ󶥵�
	Vec3d vPos;
	//���ߴ���
	double deltaValue;

	Edge(void);
	Edge(int _v1, int _v2);
	Edge(int _id, int _v1, int _v2) :id(_id), v1(_v1), v2(_v2) {};
	~Edge(void);
};