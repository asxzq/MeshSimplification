#include"meshSimplification.h"

MeshSimplification::MeshSimplification(void){
	cntEdge = 0;
	cntVertex = 0;
	cntFace_N = 0;
	cntFace_T = 10000;
}

MeshSimplification::~MeshSimplification(void) {

}

void MeshSimplification::fileRead(std::string pathNameOBJ) {
	//生成txt路径
	std::string pathNameTXT = pathNameOBJ;
	int index = pathNameOBJ.find('.');
	pathNameTXT[index + 1] = 't';
	pathNameTXT[index + 2] = 'x';
	pathNameTXT[index + 3] = 't';

	//打开文件
	std::ifstream infileTXT(pathNameTXT);
	std::ifstream infileOBJ(pathNameOBJ);
	if (!infileOBJ.is_open() || !infileTXT.is_open())
	{
		std::cout << "can not open this file" << std::endl;
		return;
	}

	//读取txt

	//读取obj
	char s;
	while (infileOBJ >> s) {
		if (s == 'v') {
			//读顶点
			cntVertex++;			
			infileOBJ >> vertexBuffer[cntVertex].position.x >> vertexBuffer[cntVertex].position.y >> vertexBuffer[cntVertex].position.z;
			vertexBuffer[cntVertex].id = cntVertex;
		}
		else if (s == '#') {
			char xxxx[100];
			infileOBJ >> xxxx;
			std::cout << "vertex read finished! cntVertex:" << cntVertex << std::endl;
			infileOBJ.getline(xxxx, 100);
		}
		else if (s == 'f') {
			cntFace_N++;
			int v1, v2, v3;
			infileOBJ >> v1 >> v2 >> v3;
			vertexBuffer[v1].neighbor.insert(v2);
			vertexBuffer[v1].neighbor.insert(v3);
			vertexBuffer[v2].neighbor.insert(v3);
			vertexBuffer[v2].neighbor.insert(v1);
			vertexBuffer[v3].neighbor.insert(v1);
			vertexBuffer[v3].neighbor.insert(v2);
		}
	}
	std::cout << "face read finished! cntFace:" << cntFace_N << std::endl;
	
	for (int i = 1; i <= cntVertex; i++) {
		std::set<int>::iterator it = vertexBuffer[i].neighbor.begin();
		for (; it != vertexBuffer[i].neighbor.end(); it++) {
			int u = std::min((*it), vertexBuffer[i].id);
			int v = std::max((*it), vertexBuffer[i].id);
			Edge e(u, v);
			calValueNVpos(e);
			addEdge(e);
		}
	}

	//关闭文件
	infileTXT.close();
	infileOBJ.close();
}

void MeshSimplification::calValueNVpos(Edge& e) {
	Mat Q_sigma = calVertexQ(e.v1) + calVertexQ(e.v2);
	
	e.vPos = calVpos(e, Q_sigma, 1);

	//必须有两个面都有这条边才能缩边
	if (vertexBuffer[e.v1].neighbor.count(e.v2) < 2) {
		e.deltaValue = 0;
		return;
	}

	int tmp = 0;

	e.deltaValue = 0;
	
}

Vec3d MeshSimplification::calVpos(Edge& e, Mat A, int flag) {
	if (flag == 0) {
		return (vertexBuffer[e.v1].position + vertexBuffer[e.v2].position) / 2;
	}
	else if (flag == 1) {
		
	}
}


Mat MeshSimplification::calVertexQ(int idVertix) {
	Mat	Q;
	Vertex* vtx = &(vertexBuffer[idVertix]);
	std::set<int>::iterator it1 = vtx->neighbor.begin();
	for (; it1 != vtx->neighbor.end(); it1++) {
		for (std::set<int>::iterator it2 = it1; it2 != vtx->neighbor.end(); it2++) {
			int u = std::min((*it1), (*it2));
			int v = std::max((*it1), (*it2));
			//如果顶点的两个邻居彼此邻接，即三点构成一个面
			if (u < v && vertexBuffer[u].neighbor.count(v)) {
				Vertex* v1 = &(vertexBuffer[u]);
				Vertex* v2 = &(vertexBuffer[v]);
				Vec3d n = ((v1->position - vtx->position)).calCross((v2->position - vtx->position)).calUnite();
				Vec4d plane(n.x, n.y, n.z, -(vtx->position.calDot(n)));
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						Q.mat[i][j] += plane.value[i] * plane.value[j];
			}
		}
	}
	return Q;
}


void MeshSimplification::addEdge(Edge& e) {
	cntEdge++;
	e.id = cntEdge;
	edge2id[std::make_pair(std::min(e.v1, e.v2), std::max(e.v1, e.v2))] = cntEdge;
	edges.push(e);
}