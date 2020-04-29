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

//QT_FORWARD_DECLARE_CLASS(SimplexMesh)

class Model3MF
{

public:
	QVector<float> vertices;// ordinal xyz
	QVector<float> newvertices;// ordinal xyzrgba
	QVector<quint32> indices;// triangle indices
	sLib3MFTransform transform;// 3*4 mat
	QVector<float> colors;// rgba
	string directory;// file dir
	bool gammaCorrection;
	QVector<PColorGroup> vecpcolorgroup;

private:
	PWrapper wrapper;
	PModel model;
public:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	float modelmin, modelmax;
	//constructor
	Model3MF(string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		xmin = 0.0f;
		xmax = 0.0f;
		ymin = 0.0f;
		ymax = 0.0f;
		zmin = 0.0f;
		zmax = 0.0f;
		modelmin = 0.0f;
		modelmax = 0.0f;

		transform.m_Fields[0][0] = 1;
		transform.m_Fields[0][1] = 0;
		transform.m_Fields[0][2] = 0;
		transform.m_Fields[1][0] = 0;
		transform.m_Fields[1][1] = 1;
		transform.m_Fields[1][2] = 0;
		transform.m_Fields[2][0] = 0;
		transform.m_Fields[2][1] = 0;
		transform.m_Fields[2][2] = 1;
		transform.m_Fields[3][0] = 0;
		transform.m_Fields[3][1] = 0;
		transform.m_Fields[3][2] = 0;

		loadModel(path);
	}

private:
	void loadModel(string const &path)
	{
		wrapper = CWrapper::loadLibrary();
		model = wrapper->CreateModel();
		PReader reader = model->QueryReader("3mf");
		// And deactivate the strict mode (default is "false", anyway. This just demonstrates where/how to use it).
		reader->SetStrictModeActive(false);
		reader->ReadFromFile(path);

		for (Lib3MF_uint32 iWarning = 0; iWarning < reader->GetWarningCount(); iWarning++)
		{
			Lib3MF_uint32 nErrorCode;
			std::string sWarningMessage = reader->GetWarning(iWarning, nErrorCode);
			std::cout << "Encountered warning #" << nErrorCode << " : " << sWarningMessage << std::endl;
		}

		Lib3MF::PBuildItemIterator buildItemIterator = model->GetBuildItems();
		while (buildItemIterator->MoveNext()) 
		{
			Lib3MF::PBuildItem buildItem = buildItemIterator->GetCurrent();
			std::cout << "Build item (Object #" << buildItem->GetObjectResourceID() << "): " << std::endl;
			if (buildItem->HasObjectTransform())
			{
				transform = buildItem->GetObjectTransform();
			}
			else
			{
				std::cout << "   Transformation:  none" << std::endl;
			}
			std::cout << "   Part number:     \"" << buildItem->GetPartNumber() << "\"" << std::endl;
		}

		PObjectIterator objectIterator = model->GetObjects();
		while (objectIterator->MoveNext()) 
		{
			PObject object = objectIterator->GetCurrentObject();
			if (object->IsMeshObject()) 
			{
				PMeshObject CurrentMesh = model->GetMeshObjectByID(object->GetResourceID());
				processMesh(CurrentMesh);
			}
			else if (object->IsComponentsObject()) {
				fprintf(stderr, "Components Object found,ID is %d", object->GetResourceID());
			}
			else 
			{
				std::cout << "unknown object #" << object->GetResourceID() << ": " << std::endl;
			}
		}
	}

	void processMesh(PMeshObject pMeshobject)

	{
		std::vector<Lib3MF::sTriangle> IndicesBuffer;
		pMeshobject->GetTriangleIndices(IndicesBuffer);

		for (unsigned int i = 0; i < pMeshobject->GetVertexCount(); i++)
		{
			float x = transform.m_Fields[0][0] * pMeshobject->GetVertex(i).m_Coordinates[0] + transform.m_Fields[1][0] * pMeshobject->GetVertex(i).m_Coordinates[1] + transform.m_Fields[2][0] * pMeshobject->GetVertex(i).m_Coordinates[2] + transform.m_Fields[3][0];
			float y = transform.m_Fields[0][1] * pMeshobject->GetVertex(i).m_Coordinates[0] + transform.m_Fields[1][1] * pMeshobject->GetVertex(i).m_Coordinates[1] + transform.m_Fields[2][1] * pMeshobject->GetVertex(i).m_Coordinates[2] + transform.m_Fields[3][1];
			float z = transform.m_Fields[0][2] * pMeshobject->GetVertex(i).m_Coordinates[0] + transform.m_Fields[1][2] * pMeshobject->GetVertex(i).m_Coordinates[1] + transform.m_Fields[2][2] * pMeshobject->GetVertex(i).m_Coordinates[2] + transform.m_Fields[3][2];

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			if (pMeshobject->GetVertex(i).m_Coordinates[0] < xmin)xmin = pMeshobject->GetVertex(i).m_Coordinates[0];
			if (pMeshobject->GetVertex(i).m_Coordinates[0] > xmax)xmax = pMeshobject->GetVertex(i).m_Coordinates[0];
			if (pMeshobject->GetVertex(i).m_Coordinates[1] < ymin)ymin = pMeshobject->GetVertex(i).m_Coordinates[1];
			if (pMeshobject->GetVertex(i).m_Coordinates[1] > ymax)ymax = pMeshobject->GetVertex(i).m_Coordinates[1];
			if (pMeshobject->GetVertex(i).m_Coordinates[2] < zmin)zmin = pMeshobject->GetVertex(i).m_Coordinates[2];
			if (pMeshobject->GetVertex(i).m_Coordinates[2] > zmax)zmax = pMeshobject->GetVertex(i).m_Coordinates[2];
		}
		modelmin = min(xmin, min(ymin, zmin));
		modelmax = max(xmax, max(ymax, zmax));

		PColorGroupIterator coloriter= model->GetColorGroups();
		while(coloriter->MoveNext())
		{
			PColorGroup colorgroup = model->GetColorGroupByID(coloriter->GetCurrent()->GetResourceID());
			vecpcolorgroup.push_back(colorgroup);
		}

		for (unsigned int i = 0; i < pMeshobject->GetTriangleCount(); i++)
		{
			sTriangle placeholder;
			_CRT_UNUSED(placeholder);
			sTriangleProperties stp;
			pMeshobject->GetTriangleProperties(i, stp);
			Lib3MF_uint8 r, g, b, a;
			for (size_t j = 0; j < sizeof(sTriangle) / sizeof(placeholder.m_Indices[0]); j++)
			{
				indices.push_back(IndicesBuffer[i].m_Indices[j]);

				float x = transform.m_Fields[0][0] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[0] + transform.m_Fields[1][0] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[1] + transform.m_Fields[2][0] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[2] + transform.m_Fields[3][0];
				float y = transform.m_Fields[0][1] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[0] + transform.m_Fields[1][1] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[1] + transform.m_Fields[2][1] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[2] + transform.m_Fields[3][1];
				float z = transform.m_Fields[0][2] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[0] + transform.m_Fields[1][2] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[1] + transform.m_Fields[2][2] * pMeshobject->GetVertex(IndicesBuffer[i].m_Indices[j]).m_Coordinates[2] + transform.m_Fields[3][2];

				newvertices.push_back(x);
				newvertices.push_back(y);
				newvertices.push_back(z);

				if (vecpcolorgroup.count())
				{
					r = model->GetColorGroupByID(stp.m_ResourceID)->GetColor(stp.m_PropertyIDs[j]).m_Red;
					g = model->GetColorGroupByID(stp.m_ResourceID)->GetColor(stp.m_PropertyIDs[j]).m_Green;
					b = model->GetColorGroupByID(stp.m_ResourceID)->GetColor(stp.m_PropertyIDs[j]).m_Blue;
					a = model->GetColorGroupByID(stp.m_ResourceID)->GetColor(stp.m_PropertyIDs[j]).m_Alpha;

					newvertices.push_back(r);
					newvertices.push_back(g);
					newvertices.push_back(b);
					newvertices.push_back(a);
				}
			}
		}
	}
};
