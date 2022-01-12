#include"edge.h"

Edge::Edge(void) {

	v1 = 0;
	v2 = 0;
	id = 0;
	//vPos = Vec3d(0, 0, 0);
	deltaValue = MAX_VALUE;
}


Edge::Edge(int _v1, int _v2) {

	v1 = _v1;
	v2 = _v2;
	id = 0;
	//vPos = Vec3d(0, 0, 0);
	deltaValue = MAX_VALUE;
}

Edge::Edge(int _id, int _v1, int _v2) {
	id = _id;
	v1 = _v1;
	v2 = _v2;
	deltaValue = MAX_VALUE;
}

Edge::~Edge(void) {

}