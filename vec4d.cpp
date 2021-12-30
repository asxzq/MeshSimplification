#include"vec4d.h"

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