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
	//����txt·��
	std::string pathNameTXT = pathNameOBJ;
	int index = pathNameOBJ.find('.');
	pathNameTXT[index + 1] = 't';
	pathNameTXT[index + 2] = 'x';
	pathNameTXT[index + 3] = 't';

	//���ļ�
	std::ifstream infileTXT(pathNameTXT);
	std::ifstream infileOBJ(pathNameOBJ);
	if (!infileOBJ.is_open() || !infileTXT.is_open())
	{
		std::cout << "can not open this file" << std::endl;
		return;
	}

	//��ȡtxt

	//��ȡobj
	char s;
	while (infileOBJ >> s) {
		if (s == 'v') {
			//������
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

	//�ر��ļ�
	infileTXT.close();
	infileOBJ.close();
}