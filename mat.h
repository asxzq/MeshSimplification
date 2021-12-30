#pragma once
class Mat
{
public:
	double mat[4][4];
	int cols = 4, rows = 4;
	Mat(void);
	~Mat(void);

	friend Mat operator + (const Mat&, const Mat&);

};

