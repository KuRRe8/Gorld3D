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
		PWrapper wrapper = CWrapper::loadLibrary();//加载库创建封皮
		PModel model = wrapper->CreateModel();//新建模型实例
		PReader reader = model->QueryReader("3mf");//读取器
		// And deactivate the strict mode (default is "false", anyway. This just demonstrates where/how to use it).
		reader->SetStrictModeActive(false);
		reader->ReadFromFile(path);


		//输出导入模型错误
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

		// 要填写的数据
		//QVector<QVector3D> vertices;
		//QVector<unsigned int> indices;
		//vector<Texture> textures;

		//先获取所有三角面索引
		std::vector<Lib3MF::sTriangle> IndicesBuffer;
		pMeshobject->GetTriangleIndices(IndicesBuffer);

		// 遍历每个网格的顶点

		for (unsigned int i = 0; i < pMeshobject->GetVertexCount(); i++)
		{
			QVector3D placeholder;
			// 位置
			placeholder.setX(pMeshobject->GetVertex(i).m_Coordinates[0]);
			placeholder.setY(pMeshobject->GetVertex(i).m_Coordinates[1]);
			placeholder.setZ(pMeshobject->GetVertex(i).m_Coordinates[2]);
			//vertices.push_back(placeholder);

			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[0]);
			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[1]);
			vertices.push_back(pMeshobject->GetVertex(i).m_Coordinates[2]);

		}
		//现在遍历每个网格面（一个面是一个三角形的网格）并检索相应的顶点索引。
		for (unsigned int i = 0; i < pMeshobject->GetTriangleCount(); i++)
		{
			sTriangle placeholder;
			for (size_t j = 0; j < sizeof(sTriangle) / sizeof(placeholder.m_Indices[0]); j++)
			{
				indices.push_back(IndicesBuffer[i].m_Indices[j]);
			}
		}
		// 返回从提取的网格数据创建的网格对象
		//return SimplexMesh(vertices, indices);

	}

};

//struct Vertex {
//	// 位置
//	glm::vec3 Position;
//	// 法向量
//	glm::vec3 Normal;
//	// 纹理坐标
//	glm::vec2 TexCoords;
//	// u向量
//	glm::vec3 Tangent;
//	// v向量
//	glm::vec3 Bitangent;
//};
struct Texture {
	unsigned int id;
	string type;
	string path;
};

class SimplexMesh {
public:
	/*  Mesh 数据  */
	QVector<QVector3D> vertices;
	QVector<unsigned int> indices;
	/*  函数  */
	// 构造函数 参数：顶点 索引 纹理
	SimplexMesh(QVector<QVector3D> vertices, QVector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
	}
private:
};
