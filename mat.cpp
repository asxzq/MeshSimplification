#include "mat.h"
Mat::Mat(void) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			mat[i][j] = 0;
}

Mat::~Mat(void) {

}

Mat operator + (const Mat& mat1, const Mat& mat2) {
	Mat ans;
	for (int i = 0; i < mat1.rows; i++)
		for (int j = 0; j < mat1.cols; j++)
			ans.mat[i][j] = mat1.mat[i][j] + mat2.mat[i][j];
	return ans;
}
