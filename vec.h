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

	//����������
	friend Vec3d operator - (const Vec3d&, const Vec3d&);
	friend Vec3d operator + (const Vec3d&, const Vec3d&);
	friend Vec3d operator - (const Vec3d&, const double&);
	friend Vec3d operator + (const Vec3d&, const double&);
	friend Vec3d operator * (const Vec3d&, const double&);
	friend Vec3d operator / (const Vec3d&, const double&);
	
	//����������ģ��
	double calNorm();
	//���������ĵ�λ����
	Vec3d calUnite();
	//������
	Vec3d calCross(const Vec3d&);
	//������
	double calDot(const Vec3d&);
};



class Vec4d {
public:
	double value[4];

	Vec4d(void);
	Vec4d(double _x, double _y, double _z, double _t);
	~Vec4d(void);
};