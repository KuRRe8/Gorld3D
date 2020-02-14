#include "Scene3d.h"

Scene3d::Scene3d(QLayout* parent)
{
	UI_Construction(parent);
	Retranslate();
	Connection_Arrangement();
}

Scene3d::~Scene3d()
{

}

bool Scene3d::LoadFromURL(QUrl *)
{
	return false;
}

void Scene3d::UI_Construction(QLayout* parent)
{
	Q_ASSERT(parent != Q_NULLPTR);//_debug runtime availability check

								  //3D view and its container
	view = new Qt3DExtras::Qt3DWindow();
	view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xf7f7f7)));//grey intention


	widget_2_1_1_1 = QWidget::createWindowContainer(view);
	//QSize screenSize = view->screen()->size();
	//widget_2_1_1_1->setMinimumSize(QSize(200, 100));
	//widget_2_1_1_1->setMaximumSize(screenSize);
	//widget_2_1_1_1->setSizePolicy(QSizePolicy::Preferred);
	parent->addWidget(widget_2_1_1_1);


	input = new Qt3DInput::QInputAspect;
	view->registerAspect(input);

	// Root entity
	rootEntity = new Qt3DCore::QEntity();

	// Camera
	cameraEntity = view->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	cameraEntity->setPosition(QVector3D(0, 0, 10.0f));// remember : z-axis is facing u from screen
	cameraEntity->setUpVector(QVector3D(0, 1, 0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

	lightEntity = new Qt3DCore::QEntity(rootEntity);
	light = new Qt3DRender::QEnvironmentLight(lightEntity);
	//light->setColor("white");
	//light->setIntensity(1);
	//Qt3DExtras::QNo
	///QUrl tU("file:\D:\\0work\\cpp\\3dp_cpp_opengl\\myQt3D\\myQt3D\\nanosuit.mtl");
	///Qt3DRender::QTextureLoader *textureldr = new Qt3DRender::QTextureLoader();
	///textureldr->setSource(tU);
	///light->setIrradiance(textureldr);
	lightEntity->addComponent(light);
	//Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	//lightTransform->setTranslation(cameraEntity->position());
	//lightEntity->addComponent(lightTransform);

	// For camera controls
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
	camController->setCamera(cameraEntity);


#pragma region(Scenemodifier)
	// Scenemodifier
	pickerentity = new Qt3DCore::QEntity(rootEntity);
	picker = new Qt3DRender::QObjectPicker();
	picker->setHoverEnabled(true);
	pickerentity->addComponent(picker);


	//m_importEntity = new Qt3DRender::QMesh();
	m_importEntity = new Qt3DCore::QEntity(rootEntity);
	///m_importMesh = new Qt3DRender::QMesh(m_importEntity);

	m_importSceneLoader = new Qt3DRender::QSceneLoader(m_importEntity);
	//QUrl importobjectURL("file:///D:\\0work\\cpp\\3dp_cpp_opengl\\myQt3D\\myQt3D\\nanosuit.obj");
	QUrl importobjectURL("file:///D:\\0work\\modal\\pikachu\\pikaqiu.obj");
	QString st = importobjectURL.toString();
	st = importobjectURL.fileName();
	////connect(m_importSceneLoader, SIGNAL(sourceChanged(QUrl & importobjectURL)), this, SLOT(receiveSourceChanged(QUrl & source)));

	m_importSceneLoader->setSource(importobjectURL);
	m_importSceneLoader->setEnabled(true);
	//! [1]设置变换component
	Qt3DCore::QTransform *importTransform = new Qt3DCore::QTransform();
	importTransform->setScale(0.1f);
	importTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 25.0f));
	importTransform->setTranslation(QVector3D(0.0f, -1.0f, 0.0f));
	//! [1]

	////! [2]设置漫反射
	Qt3DExtras::QPhongMaterial *importMaterial = new Qt3DExtras::QPhongMaterial();
	importMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
	////! [2]

	//! [3]加载各component到根实体（entity/node）
	m_importEntity->addComponent(m_importSceneLoader);
	//m_importEntity->addComponent(importMaterial);
	m_importEntity->addComponent(importTransform);
	//! [3]

	//uchar importStatus = m_importSceneLoader->status();
	//QStringList m_importSceneStringList = m_importSceneLoader->entityNames();

#pragma endregion 


	// Set root object of the scene
	view->setRootEntity(rootEntity);


}

void Scene3d::Retranslate()
{
}

void Scene3d::Connection_Arrangement()
{
	QObject::connect(picker, SIGNAL(entered()), this, SLOT(slot_entered_picker()));

}

void Scene3d::slot_entered_picker()
{
	;
}