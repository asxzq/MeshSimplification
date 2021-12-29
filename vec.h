#pragma once
#include<iostream>
#include<cmath>

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
};
