#pragma once
#include<iostream>
#include<cmath>

class Vec3d {
public:
	double x, y, z;
	
	Vec3d(void);
	~Vec3d(void);
	Vec3d(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	//定义计算符号
	friend Vec3d operator - (const Vec3d&, const Vec3d&);
	friend Vec3d operator + (const Vec3d&, const Vec3d&);
	friend Vec3d operator - (const Vec3d&, const double&);
	friend Vec3d operator + (const Vec3d&, const double&);
	friend Vec3d operator * (const Vec3d&, const double&);
	friend Vec3d operator / (const Vec3d&, const double&);
	
	//计算向量的模长
	double calNorm();
	//计算向量的单位向量
	Vec3d calUnite();
};
