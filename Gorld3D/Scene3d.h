#pragma once
/*
implementation of 3D view. under QStackedLayout* stackedlayout_2_1_1_ 
*/
#include "__Utilities.h"

#include <QtCore/QObject>
#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QMesh> 
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qobjectpicker.h>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DInput/QInputAspect>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>
#include <Qt3DExtras/qorbitcameracontroller.h>
#include <Qt3DRender/qenvironmentlight.h>
#include <Qt3DRender/qspotlight.h>
#include <Qt3DRender/qdirectionallight.h>
#include <Qt3DRender/qmaterial.h>

#include "qstackedlayout.h"

class Scene3d : public QObject
{
	Q_OBJECT
public:
	explicit Scene3d(QStackedLayout* parent);
	virtual ~Scene3d();

	//static QLayout* pContainerLayout;
	//static void setContainerLayout(QLayout* parent);
	bool LoadFromURL(QUrl*);
private:
	void UI_Construction(QStackedLayout* parent);
	void Retranslate();
	void Connection_Arrangement();

	Qt3DExtras::Qt3DWindow * view;
	QWidget* widget_2_1_1_1;//includs the Qt3DExtras::Qt3DWindow * view; father is QStackedLayout* stackedlayout_2_1_1_
	Qt3DInput::QInputAspect *input;//handle input
	Qt3DCore::QEntity *rootEntity;
	Qt3DRender::QCamera *cameraEntity;
	Qt3DCore::QEntity *lightEntity;
	Qt3DRender::QEnvironmentLight *light;
	Qt3DCore::QEntity *pickerentity;
	Qt3DRender::QObjectPicker *picker;
	Qt3DCore::QEntity *m_importEntity;
	Qt3DRender::QSceneLoader *m_importSceneLoader;


signals:
	;
private slots:
	void slot_entered_picker();

};

//QLayout* Scene3d::pContainerLayout = Q_NULLPTR;
//
//FORCEINLINE void Scene3d::setContainerLayout(QLayout* parent)
//{
//	pContainerLayout = parent;
//}