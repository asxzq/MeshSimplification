#include"meshSimplification.h"

MeshSimplification::MeshSimplification(void){
	cntFace = 0;
	cntEdge = 0;
	cntVertex = 0;
	cntFace_N = 0;
	cntFace_T = 2000000;
	for (int i = 0; i < MAX_EDGE_CNT; i++)
		edgeDeleted[i] = false;
	for (int i = 0; i < MAX_VERTEX_CNT; i++)
		vertexDeleted[i] = false;
	for (int i = 0; i < MAX_FACE_CNT; i++)
		faceDeleted[i] = false;
	for (int i = 0; i < MAX_VERTEX_CNT; i++)
		vertexTimes[i] = 0;
}

MeshSimplification::~MeshSimplification(void) {

}

void MeshSimplification::fileRead(std::string pathNameOBJ) {
	//打开文件
	std::ifstream infileOBJ(pathNameOBJ);
	if (!infileOBJ.is_open())
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
			cntFace++;
			int v1, v2, v3;
			infileOBJ >> v1 >> v2 >> v3;

			vertexTimes[v1] ++;
			vertexTimes[v2] ++;
			vertexTimes[v3] ++;

			faceBuffer[cntFace].id = cntFace;
			faceBuffer[cntFace].idVertex1 = v1;
			faceBuffer[cntFace].idVertex2 = v2;
			faceBuffer[cntFace].idVertex3 = v3;
			
			vertexBuffer[v1].faces.insert(cntFace);
			vertexBuffer[v2].faces.insert(cntFace);
			vertexBuffer[v3].faces.insert(cntFace);

			vertexBuffer[v1].neighbor.insert(v2);
			vertexBuffer[v1].neighbor.insert(v3);
			vertexBuffer[v2].neighbor.insert(v3);
			vertexBuffer[v2].neighbor.insert(v1);
			vertexBuffer[v3].neighbor.insert(v1);
			vertexBuffer[v3].neighbor.insert(v2);

		}
	}
	std::cout << "face read finished! cntFace:" << cntFace_N  << std::endl;
	

	//关闭文件
	infileOBJ.close();
}

void MeshSimplification::edgeCollapse(int faceTarget) {
	if(cntFace_T > faceTarget)
		cntFace_T = faceTarget;
	
	for (int i = 1; i <= cntVertex; i++) {
		std::set<int>::iterator it = vertexBuffer[i].neighbor.begin();
		for (; it != vertexBuffer[i].neighbor.end(); it++) {
			//定向加边，避免重复
			if (i > (*it)) {
				Edge e((*it), i);
				calValueNVpos(e);
				addEdge(e);
			}
		}
	}

	std::cout << "edge init finished! cntEdge:" << cntEdge << std::endl;

	//for (; cntFace_N > cntFace_T; cntFace_N -= 2) {
	while(cntFace_N>cntFace_T){

		if(cntFace_N % 1000 == 0 || cntFace_N % 1000 == 1)
			std::cout << cntFace_N << std::endl;
		//取出点
		Edge edgeMIN = getEdgeWithMINDeltaValue();


		/* 调试代码
		std::cout << cntFace_N << " " << edgeMIN.id << std::endl;
		Edge edgeMIN(1923,3641);
		calValueNVpos(edgeMIN);

		std::cout << edgeMIN.deltaValue << " " << "->" << std::endl;
		
		Mat Q_sigma = calVertexQ(edgeMIN.v1) + calVertexQ(edgeMIN.v2);
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				std::cout << Q_sigma.mat[x][y] << " ";
			}
			std::cout << std::endl;
		}

		edgeMIN.vPos = calVpos(edgeMIN, Q_sigma, 1);
		std::cout << edgeMIN.vPos.x << " " << edgeMIN.vPos.y << " " << edgeMIN.vPos.z << " " << std::endl;
		std::cout << edgeMIN.deltaValue << " " << std::endl;
		*/
		
		Vertex* v1 = &(vertexBuffer[edgeMIN.v1]);
		Vertex* v2 = &(vertexBuffer[edgeMIN.v2]);

		//在顶点集合中加入新点
		cntVertex++;
		Vertex* vNew = &(vertexBuffer[cntVertex]);
		vNew->position = edgeMIN.vPos;
		vNew->id = cntVertex;

		//删除edgeMIN和顶点
		deleteEdge(edgeMIN);
		vertexDeleted[v1->id] = true;
		vertexDeleted[v2->id] = true;

		/*
		for (std::set<int>::iterator it = v1->neighbor.begin(); it != v1->neighbor.end(); it++) {
			std::cout << (*it) << " ";
		}
		std::cout << std::endl;
		for (std::set<int>::iterator it = v2->neighbor.begin(); it != v2->neighbor.end(); it++) {
			std::cout << (*it) << " ";
		}
		std::cout << std::endl;
		*/

		for (std::set<int>::iterator it = v1->neighbor.begin(); it != v1->neighbor.end(); it++) {
			if ((*it) != v2->id) {
				//删除与v1的所有边
				deleteEdge((*it), v1->id);
				//解除邻接关系
				vertexBuffer[(*it)].neighbor.erase(v1->id);
				//添加邻接关系
				vertexBuffer[cntVertex].neighbor.insert((*it));
				vertexBuffer[(*it)].neighbor.insert(cntVertex);
			}
		}

		for (std::set<int>::iterator it = v2->neighbor.begin(); it != v2->neighbor.end(); it++) {
			if ((*it) != v1->id) {
				//删除与v1的所有边
				deleteEdge((*it), v2->id);
				//解除邻接关系
				vertexBuffer[(*it)].neighbor.erase(v2->id);
				//添加邻接关系
				vertexBuffer[cntVertex].neighbor.insert((*it));
				vertexBuffer[(*it)].neighbor.insert(cntVertex);
			}
		}
		

		//std::cout << v1->id << " " << v2->id <<  "->>>" << vNew->id << std::endl;
		//std::cout << std::endl;

		std::vector<int> faceDeleting;

		for (std::set<int>::iterator it = v1->faces.begin(); it != v1->faces.end(); it++) {
			
			Face* f = &(faceBuffer[(*it)]);
			//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
			if (f->idVertex1 == v1->id)
				f->idVertex1 = vNew->id;
			else if (f->idVertex2 == v1->id)
				f->idVertex2 = vNew->id;
			else if (f->idVertex3 == v1->id)
				f->idVertex3 = vNew->id;
			//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
			vNew->faces.insert(f->id);
		}
		//std::cout << std::endl;

		for (std::set<int>::iterator it = v2->faces.begin(); it != v2->faces.end(); it++) {
			Face* f = &(faceBuffer[(*it)]);
			//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
			if (f->idVertex1 == v2->id)
				f->idVertex1 = vNew->id;
			else if (f->idVertex2 == v2->id)
				f->idVertex2 = vNew->id;
			else if (f->idVertex3 == v2->id)
				f->idVertex3 = vNew->id;
			//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
			vNew->faces.insert(f->id);

			//若一个面有两个顶点重合，则删除
			if (f->idVertex1 == f->idVertex2) {
				faceDeleting.push_back(f->id);
				vertexBuffer[f->idVertex3].faces.erase(f->id);
				//std::cout << "delete face iD: " << f->id << std::endl;
			}
			else if (f->idVertex2 == f->idVertex3) {
				faceDeleting.push_back(f->id);
				vertexBuffer[f->idVertex1].faces.erase(f->id);
			}
			else if (f->idVertex3 == f->idVertex1){
				faceDeleting.push_back(f->id);
				vertexBuffer[f->idVertex2].faces.erase(f->id);
			}
				
		}

		for (int i = 0; i < faceDeleting.size(); i++) {
			vNew->faces.erase(faceDeleting[i]);
			faceDeleted[faceDeleting[i]] = true;
			cntFace_N--;
		}

		/*
		for (std::set<int>::iterator it = vertexBuffer[cntVertex].neighbor.begin(); it != vertexBuffer[cntVertex].neighbor.end(); it++) {
			std::cout << (*it) << " ";
		}*/
		//填入优先序列
		for (std::set<int>::iterator it = vNew->neighbor.begin(); it != vNew->neighbor.end(); it++) {
			Edge e((*it), cntVertex);
			calValueNVpos(e);
			addEdge(e);
		}
	}
}




void MeshSimplification::edgeCollapseSingle(int idVertex1, int idVertex2) {
	
	Edge edgeMIN(idVertex1, idVertex2);
	calValueNVpos(edgeMIN);

	Mat Q_sigma;

	Vertex* v1 = &(vertexBuffer[idVertex1]);
	Vertex* v2 = &(vertexBuffer[idVertex2]);

	//在顶点集合中加入新点
	cntVertex++;
	Vertex* vNew = &(vertexBuffer[cntVertex]);
	vNew->position = calVpos(edgeMIN, Q_sigma, 0);
	vNew->id = cntVertex;

	//删除edgeMIN和顶点
	deleteEdge(edgeMIN);
	vertexDeleted[v1->id] = true;
	vertexDeleted[v2->id] = true;

	for (std::set<int>::iterator it = v1->neighbor.begin(); it != v1->neighbor.end(); it++) {
		if ((*it) != v2->id) {
			//删除与v1的所有边
			deleteEdge((*it), v1->id);
			//解除邻接关系
			vertexBuffer[(*it)].neighbor.erase(v1->id);
			//添加邻接关系
			vertexBuffer[cntVertex].neighbor.insert((*it));
			vertexBuffer[(*it)].neighbor.insert(cntVertex);
		}
	}

	for (std::set<int>::iterator it = v2->neighbor.begin(); it != v2->neighbor.end(); it++) {
		if ((*it) != v1->id) {
			//删除与v1的所有边
			deleteEdge((*it), v2->id);
			//解除邻接关系
			vertexBuffer[(*it)].neighbor.erase(v2->id);
			//添加邻接关系
			vertexBuffer[cntVertex].neighbor.insert((*it));
			vertexBuffer[(*it)].neighbor.insert(cntVertex);
		}
	}

	std::vector<int> faceDeleting;

	for (std::set<int>::iterator it = v1->faces.begin(); it != v1->faces.end(); it++) {

		Face* f = &(faceBuffer[(*it)]);
		//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
		if (f->idVertex1 == v1->id)
			f->idVertex1 = vNew->id;
		else if (f->idVertex2 == v1->id)
			f->idVertex2 = vNew->id;
		else if (f->idVertex3 == v1->id)
			f->idVertex3 = vNew->id;
		//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
		vNew->faces.insert(f->id);
	}
	//std::cout << std::endl;

	for (std::set<int>::iterator it = v2->faces.begin(); it != v2->faces.end(); it++) {
		Face* f = &(faceBuffer[(*it)]);
		//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
		if (f->idVertex1 == v2->id)
			f->idVertex1 = vNew->id;
		else if (f->idVertex2 == v2->id)
			f->idVertex2 = vNew->id;
		else if (f->idVertex3 == v2->id)
			f->idVertex3 = vNew->id;
		//std::cout << f->id << ": " << f->idVertex1 << " " << f->idVertex2 << " " << f->idVertex3 << std::endl;
		vNew->faces.insert(f->id);

		//若一个面有两个顶点重合，则删除
		if (f->idVertex1 == f->idVertex2) {
			faceDeleting.push_back(f->id);
			vertexBuffer[f->idVertex3].faces.erase(f->id);
			//std::cout << "delete face iD: " << f->id << std::endl;
		}
		else if (f->idVertex2 == f->idVertex3) {
			faceDeleting.push_back(f->id);
			vertexBuffer[f->idVertex1].faces.erase(f->id);
		}
		else if (f->idVertex3 == f->idVertex1) {
			faceDeleting.push_back(f->id);
			vertexBuffer[f->idVertex2].faces.erase(f->id);
		}

	}

	for (int i = 0; i < faceDeleting.size(); i++) {
		vNew->faces.erase(faceDeleting[i]);
		faceDeleted[faceDeleting[i]] = true;
		cntFace_N--;
	}

	for (std::set<int>::iterator it = vNew->neighbor.begin(); it != vNew->neighbor.end(); it++) {
		Edge e((*it), cntVertex);
		calValueNVpos(e);
		addEdge(e);
	}
}



Edge MeshSimplification::getEdgeWithMINDeltaValue() {
	if (edges.size()<=0)
		return Edge(0, 0);
	while (edgeDeleted[edges.top().id])
		edges.pop();
	Edge e = edges.top();
	edges.pop();
	return e;
}



void MeshSimplification::calValueNVpos(Edge& e) {
	Mat Q_sigma = calVertexQ(e.v1) + calVertexQ(e.v2);
	
	e.vPos = calVpos(e, Q_sigma, 1);

	double vPos4d[4] = { e.vPos.x, e.vPos.y, e.vPos.z, 1 };
	//必须有两个面都有这条边才能缩边
	if (!vertexBuffer[e.v1].neighbor.count(e.v2)) {
		e.deltaValue = 99999999;
		return;
	}

	double tmp = 0;

	tmp += vPos4d[0] * (vPos4d[0] * Q_sigma.mat[0][0] + vPos4d[1] * Q_sigma.mat[1][0] + vPos4d[2] * Q_sigma.mat[2][0] + vPos4d[3] * Q_sigma.mat[3][0]);
	tmp += vPos4d[1] * (vPos4d[0] * Q_sigma.mat[0][1] + vPos4d[1] * Q_sigma.mat[1][1] + vPos4d[2] * Q_sigma.mat[2][1] + vPos4d[3] * Q_sigma.mat[3][1]);
	tmp += vPos4d[2] * (vPos4d[0] * Q_sigma.mat[0][2] + vPos4d[1] * Q_sigma.mat[1][2] + vPos4d[2] * Q_sigma.mat[2][2] + vPos4d[3] * Q_sigma.mat[3][2]);
	tmp += vPos4d[3] * (vPos4d[0] * Q_sigma.mat[0][3] + vPos4d[1] * Q_sigma.mat[1][3] + vPos4d[2] * Q_sigma.mat[2][3] + vPos4d[3] * Q_sigma.mat[3][3]);
	
	e.deltaValue = tmp;
}

Vec3d MeshSimplification::calVpos(Edge& e, Mat m, int flag) {
	if (flag == 0) {
		return (vertexBuffer[e.v1].position + vertexBuffer[e.v2].position) / 2;
	}
	else if (flag == 1) {
		m.mat[3][0] = 0;
		m.mat[3][1] = 0;
		m.mat[3][2] = 0;
		m.mat[3][3] = 1;
		Vec4d b(0, 0, 0, 1);
		Vec4d x(0, 0, 0, 1);
		//消元法
		for (int i = 0; i < 4; i++) {
			int j = 0;
			while (j < 4 && fabs(m.mat[i][j]) < EPS)
				j++;
			if (j == 4)
				continue;
			for (int k = 0; k < 4; k++) {
				if (k != i) {
					double rate = m.mat[k][j] / m.mat[i][j];
					for (int l = 0; l < 4; l++)
						m.mat[k][l] -= m.mat[i][l] * rate;
					b.value[k] -= b.value[i] * rate;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			int j = 0;
			while (j < 4 && fabs(m.mat[i][j]) < EPS)
				j++;
			if (j == 4)
				return Vec3d(0, 0, 0);
			x.value[i] = b.value[i] / m.mat[i][j];
		}
		if(x.value[3] > EPS)
			return Vec3d(x.value[0], x.value[1], x.value[2]);
		else
			return (vertexBuffer[e.v1].position + vertexBuffer[e.v2].position) / 2;
	}
}


Mat MeshSimplification::calVertexQ(int idVertex) {
	Mat	Q;
	
	Vertex* vtx = &(vertexBuffer[idVertex]);
	/*
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
	*/
	std::set<int>::iterator it2 = vtx->faces.begin();
	for (; it2 != vtx->faces.end(); it2++) {
		Face* face = &(faceBuffer[(*it2)]);
		Vertex* v1 = &(vertexBuffer[face->idVertex1]);
		Vertex* v2 = &(vertexBuffer[face->idVertex2]);
		Vertex* v3 = &(vertexBuffer[face->idVertex3]);
		Vec3d n = ((v1->position - v3->position).calCross(v2->position - v3->position)).calUnite();
		Vec4d plane(n.x, n.y, n.z, -(v3->position.calDot(n)));
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				Q.mat[i][j] += plane.value[i] * plane.value[j];
	}
	return Q;
}


void MeshSimplification::addEdge(Edge& e) {
	cntEdge++;
	e.id = cntEdge;
	edge2id[std::make_pair(std::min(e.v1, e.v2), std::max(e.v1, e.v2))] = cntEdge;
	edges.push(e);
}

void MeshSimplification::deleteEdge(Edge& e) {
	if(e.v1 < e.v2)
		edgeDeleted[edge2id[std::make_pair(e.v1, e.v2)]] = true;
	else
		edgeDeleted[edge2id[std::make_pair(e.v2, e.v1)]] = true;
}
void MeshSimplification::deleteEdge(int id1, int id2) {
	if(id1 < id2)
		edgeDeleted[edge2id[std::make_pair(id1, id2)]] = true;
	else
		edgeDeleted[edge2id[std::make_pair(id2, id1)]] = true;
}


void MeshSimplification::fileWrite(std::string pathNameOBJ) {

	std::ofstream outfileOBJ(pathNameOBJ, std::ios::trunc);
	//恢复计数
	int cntVertexTrue = 0;

	int cntFaceTrue = 0;
	for (int i = 1; i <= cntVertex; i++) {
		if (vertexDeleted[i])
			continue;
		cntVertexTrue++;
		Vertex* v = &(vertexBuffer[i]);
		v->id = cntVertexTrue;
		outfileOBJ << "v " << v->position.x << " " << v->position.y << " " << v->position.z << std::endl;
	}
	for (int i = 1; i <= cntFace; i++) {
		if (faceDeleted[i])
			continue;
		cntFaceTrue++;
		Face* f = &(faceBuffer[i]);
		outfileOBJ << "f " << vertexBuffer[f->idVertex1].id << " " << vertexBuffer[f->idVertex2].id << " " << vertexBuffer[f->idVertex3].id << std::endl;
	}
	std::cout << "face: " << cntFaceTrue << std::endl;
}

