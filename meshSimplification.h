#pragma once
#include<iostream>
#include"vertex.h"
#include"edge.h"
#include<fstream>
#include<string>
#include<queue>
#include<map>
#define MAX_VERTEX_CNT 100000
#define MAX_EDGE_CNT 200000

class MeshSimplification {
	
	
	//现有面数
	int cntFace_N;
	//目标面数
	int cntFace_T;


	//点相关变量
	//顶点数
	int cntVertex;
	//点集
	Vertex vertexBuffer[MAX_VERTEX_CNT];
	//标记是否已被删除
	bool vertexDeleted[MAX_VERTEX_CNT + 1];


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
	map<pair<int, int>, int> edge2id;


public:
	MeshSimplification(void);
	~MeshSimplification(void);
	
	//流程主体函数
	//读取OBJ文件
	void fileRead(std::string pathNameOBJ);





	//边相关函数
	//增加边
	void addEdge(Edge&);
	

};