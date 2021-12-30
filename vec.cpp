#include"vec.h"

Vec3d::Vec3d(void)
{
	x = 0;
	y = 0;
	z = 0;
}
Vec3d::~Vec3d(void)
{

}

Vec3d operator - (const Vec3d& a, const Vec3d& b) {
	return Vec3d(a.x - b.x, a.y - b.y, a.z - b.z);
}
Vec3d operator + (const Vec3d& a, const Vec3d& b) {
	return Vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
}
Vec3d operator - (const Vec3d& a, const double& c) {
	return Vec3d(a.x - c, a.y - c, a.z - c);
}
Vec3d operator + (const Vec3d& a, const double& c) {
	return Vec3d(a.x + c, a.y + c, a.z + c);
}
Vec3d operator * (const Vec3d& a, const double& c) {
	return Vec3d(a.x * c, a.y * c, a.z * c);
}
Vec3d operator / (const Vec3d& a, const double& c) {
	return Vec3d(a.x / c, a.y / c, a.z / c);
}
double Vec3d::calNorm() {
	return sqrt(x * x + y * y + z * z);
}
Vec3d Vec3d::calUnite() {
	return *this / this->calNorm();
}
Vec3d Vec3d::calCross(const Vec3d& b) {
	return Vec3d(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
}
double Vec3d::calDot(const Vec3d& b) {
	return x * b.x + y * b.y + z * b.z;
}


Vec4d::Vec4d(void) {
	value[0] = 0;
	value[1] = 0;
	value[2] = 0;
	value[3] = 0;
}

Vec4d::Vec4d(double _x, double _y, double _z, double _t) {
	value[0] = _x;
	value[1] = _y;
	value[2] = _z;
	value[3] = _t;
}


Vec4d::~Vec4d(void) {

}
