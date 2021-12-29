#include"vec.h"
#define EPS 1e-7
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
