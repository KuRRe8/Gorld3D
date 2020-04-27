#pragma once
#include "__Utilities.h"
#include <lib3mf_implicit.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <qvector.h>

using namespace std;
using namespace Lib3MF;

QT_FORWARD_DECLARE_CLASS(SimplexMesh)

class Model3MF
{
public:
//	vector<Texture> textures_loaded;
//	QVector<QVector3D> vertices;
	QVector<float> vertices;
	QVector<quint32> indices;
	string directory;
	bool gammaCorrection;

	//constructor
	Model3MF(string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}

	//void Draw(Shader shader)
	//{
	//	for (unsigned int i = 0; i < meshes.size(); i++)
	//		meshes[i].Draw(shader);
	//}
private:
	void loadModel(string const &path)
	{
		PWrapper wrapper = CWrapper::loadLibrary();//���ؿⴴ����Ƥ
		PModel model = wrapper->CreateModel();//�½�ģ��ʵ��
		PReader reader = model->QueryReader("3mf");//��ȡ��
		// And deactivate the strict mode (default is "false", anyway. This just demonstrates where/how to use it).
		reader->SetStrictModeActive(false);
		reader->ReadFromFile(path);


		//�������ģ�ʹ���
		for (Lib3MF_uint32 iWarning = 0; iWarning < reader->GetWarningCount(); iWarning++) {
			Lib3MF_uint32 nErrorCode;
			std::string sWarningMessage = reader->GetWarning(iWarning, nErrorCode);
			std::cout << "Encountered warning #" << nErrorCode << " : " << sWarningMessage << std::endl;
		}

		PObjectIterator objectIterator = model->GetObjects();
		while (objectIterator->MoveNext()) {
			PObject object = objectIterator->GetCurrentObject();
			if (object->IsMeshObject()) {
				PMeshObject CurrentMesh = model->GetMeshObjectByID(object->GetResourceID());
				processMesh(CurrentMesh);
			}
			else if (object->IsComponentsObject()) {
				fprintf(stderr, "Components Object found,ID is %d", object->GetResourceID());
			}
			else {
				std::cout << "unknown object #" << object->GetResourceID() << ": " << std::endl;
			}
		}
	}

	void processMesh(PMeshObject pMeshobject)

	{

		// Ҫ��д������
		//QVector<QVector3D> vertices;
		//QVector<unsigned int> indices;
		//vector<Texture> textures;

		//�Ȼ�ȡ��������������
		std::vector<Lib3MF::sTriangle> IndicesBuffer;
		pMeshobject->GetTriangleIndices(IndicesBuffer);

		// ����ÿ������Ķ���

		for (unsigned int i = 0; i < pMeshobject->GetVertexCount(); i++)
		{
			QVector3D placeholder;
			// λ��
			placeholder.setX(pMeshobject->GetVertex(i).m_Coordinates[0]);
			placeholder.setY(pMeshobject->GetVertex(i).m_Coordinates[1]);
			placeholder.setZ(pMeshobject->GetVertex(i).m_Coordinates[2]);
			//vertices.push_back(placeholder);

			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[0]);
			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[1]);
			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[2]);

		}
		//���ڱ���ÿ�������棨һ������һ�������ε����񣩲�������Ӧ�Ķ���������
		for (unsigned int i = 0; i < pMeshobject->GetTriangleCount(); i++)
		{
			sTriangle placeholder;
			for (size_t j = 0; j < sizeof(sTriangle) / sizeof(placeholder.m_Indices[0]); j++)
			{
				indices.push_back(IndicesBuffer[i].m_Indices[j]);
			}
		}
		// ���ش���ȡ���������ݴ������������
		//return SimplexMesh(vertices, indices);

	}

};

//struct Vertex {
//	// λ��
//	glm::vec3 Position;
//	// ������
//	glm::vec3 Normal;
//	// ��������
//	glm::vec2 TexCoords;
//	// u����
//	glm::vec3 Tangent;
//	// v����
//	glm::vec3 Bitangent;
//};
struct Texture {
	unsigned int id;
	string type;
	string path;
};

class SimplexMesh {
public:
	/*  Mesh ����  */
	QVector<QVector3D> vertices;
	QVector<unsigned int> indices;
	/*  ����  */
	// ���캯�� ���������� ���� ����
	SimplexMesh(QVector<QVector3D> vertices, QVector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
private:
};
