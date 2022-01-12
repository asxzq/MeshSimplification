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
	
	
	//��������
	int cntFace_N;
	//Ŀ������
	int cntFace_T;


	//����ر���
	//������
	int cntVertex;
	//�㼯
	Vertex vertexBuffer[MAX_VERTEX_CNT + 1];
	//����Ƿ��ѱ�ɾ��
	bool vertexDeleted[MAX_VERTEX_CNT + 1];

	int vertexTimes[MAX_VERTEX_CNT + 1];


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


	//����ر���
	//����
	int cntFace;
	//�漯��
	Face faceBuffer[MAX_FACE_CNT + 1];
	//����Ƿ��ѱ�ɾ��
	bool faceDeleted[MAX_EDGE_CNT + 1];


public:
	MeshSimplification(void);
	~MeshSimplification(void);
	
	//�������庯��
	//��ȡOBJ�ļ�
	void fileRead(std::string pathNameOBJ);
	void edgeCollapse(int faceTarget);
	//basic1
	void edgeCollapseSingle(int idVertex1, int idVertex2);
	void fileWrite(std::string pathNameOBJ);


	//������غ���
	//������۾���
	Mat calVertexQ(int idVertex);


	//����غ���
	//���ӱ�
	void addEdge(Edge&);
	//ɾ����
	void deleteEdge(Edge&);
	void deleteEdge(int id1, int id2);
	//�������ߵĶ���ʹ���
	void calValueNVpos(Edge&);
	//�������ߵĶ���
	Vec3d calVpos(Edge&, Mat A, int flag);
	//ȡ��deltaValue��С�ĵ�
	Edge getEdgeWithMINDeltaValue();

};