#pragma once
#include<iostream>
#include<set>
#include"vec.h"
class Vertex {
public:
	//顶点索引>=1
	int id;
	//位置
	Vec3d position;
	//相邻点
	std::set<int> neighbor;

	//创建顶点
	Vertex(void) :id(0), position(Vec3d(0, 0, 0)) {};
	~Vertex(void);
	Vertex(Vec3d _position) :id(0), position(_position) {};
	Vertex(double _x, double _y, double _z) :id(-1), position(Vec3d(_x, _y, _z)) {};
	Vertex(int _id, Vec3d _position) :id(_id), position(_position) {};
	Vertex(int _id, double _x, double _y, double _z) :id(_id), position(Vec3d(_x, _y, _z)) {};

};