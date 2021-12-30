#pragma once

class Vec4d {
public:
	double value[4];

	Vec4d(void);
	Vec4d(double _x, double _y, double _z, double _t);
	~Vec4d(void);
};