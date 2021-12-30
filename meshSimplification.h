#pragma once
#include<iostream>
#include"vertex.h"
#include"edge.h"
#include"mat.h"
#include<fstream>
#include<string>
#include<queue>
#include<map>
#define MAX_VERTEX_CNT 100000
#define MAX_EDGE_CNT 200000

class MeshSimplification {
	
	
	//��������
	int cntFace_N;
	//Ŀ������
	int cntFace_T;


	//����ر���
	//������
	int cntVertex;
	//�㼯
	Vertex vertexBuffer[MAX_VERTEX_CNT];
	//����Ƿ��ѱ�ɾ��
	bool vertexDeleted[MAX_VERTEX_CNT + 1];


	//����ر���
	//�ȽϺ���
	struct cmp {
		bool operator()(Edge e1, Edge e2) {
			return e1.deltaValue > e2.deltaValue;
		}
	};
	//����
	int cntEdge;
	//�ߵ����ȶ���----����ȡ����С���۱�
	std::priority_queue<Edge, std::vector<Edge>, cmp> edges;
	//����Ƿ��ѱ�ɾ��
	bool edgeDeleted[MAX_EDGE_CNT + 1];
	//�ߵ�����ͼ��----���ڷ��ʱߵ�����
	std::map<std::pair<int, int>, int> edge2id;


public:
	MeshSimplification(void);
	~MeshSimplification(void);
	
	//�������庯��
	//��ȡOBJ�ļ�
	void fileRead(std::string pathNameOBJ);


	//������غ���
	//������۾���
	Mat calVertexQ(int idVertex);


	//����غ���
	//���ӱ�
	void addEdge(Edge&);
	//�������ߵĶ���ʹ���
	void calValueNVpos(Edge&);
	//�������ߵĶ���
	Vec3d calVpos(Edge&, Mat A, int flag);

};