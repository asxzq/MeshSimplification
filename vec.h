#pragma once
#include<iostream>
#include<cmath>
#define EPS 1e-7

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
	//计算叉乘
	Vec3d calCross(const Vec3d&);
	//计算点乘
	double calDot(const Vec3d&);
};



class Vec4d {
public:
	double value[4];

	Vec4d(void);
	Vec4d(double _x, double _y, double _z, double _t);
	~Vec4d(void);
};