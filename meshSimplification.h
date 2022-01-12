#pragma once
#include<iostream>
#include"vertex.h"
#include"edge.h"
#include"mat.h"
#include"face.h"
#include<fstream>
#include<string>
#include<queue>
#include<map>
#define MAX_VERTEX_CNT 10000000
#define MAX_EDGE_CNT 20000000
#define MAX_FACE_CNT 20000000

class MeshSimplification {
	
	
	//现有面数
	int cntFace_N;
	//目标面数
	int cntFace_T;


	//点相关变量
	//顶点数
	int cntVertex;
	//点集
	Vertex vertexBuffer[MAX_VERTEX_CNT + 1];
	//标记是否已被删除
	bool vertexDeleted[MAX_VERTEX_CNT + 1];

	int vertexTimes[MAX_VERTEX_CNT + 1];


	//边相关变量
	//比较函数
	struct cmp {
		bool operator()(Edge e1, Edge e2) {
			return e1.deltaValue > e2.deltaValue;
		}
	};
	//边数
	int cntEdge;
	//边的优先队列----便于取出最小代价边
	std::priority_queue<Edge, std::vector<Edge>, cmp> edges;
	//标记是否已被删除
	bool edgeDeleted[MAX_EDGE_CNT + 1];
	//边的索引图表----便于访问边的索引
	std::map<std::pair<int, int>, int> edge2id;


	//面相关变量
	//面数
	int cntFace;
	//面集合
	Face faceBuffer[MAX_FACE_CNT + 1];
	//标记是否已被删除
	bool faceDeleted[MAX_EDGE_CNT + 1];


public:
	MeshSimplification(void);
	~MeshSimplification(void);
	
	//流程主体函数
	//读取OBJ文件
	void fileRead(std::string pathNameOBJ);
	void edgeCollapse(int faceTarget);
	//basic1
	void edgeCollapseSingle(int idVertex1, int idVertex2);
	void fileWrite(std::string pathNameOBJ);


	//顶点相关函数
	//计算代价矩阵
	Mat calVertexQ(int idVertex);


	//边相关函数
	//增加边
	void addEdge(Edge&);
	//删除边
	void deleteEdge(Edge&);
	void deleteEdge(int id1, int id2);
	//计算缩边的顶点和代价
	void calValueNVpos(Edge&);
	//计算缩边的顶点
	Vec3d calVpos(Edge&, Mat A, int flag);
	//取出deltaValue最小的点
	Edge getEdgeWithMINDeltaValue();

};