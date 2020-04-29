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



#pragma region(3DView)
	//3D view and its container
	view = new Qt3DExtras::Qt3DWindow();
	view->defaultFrameGraph()->setClearColor(QColor(QRgb(0xf7f7f7)));//grey intention


	widget_2_1_1_1 = QWidget::createWindowContainer(view);
	//QSize screenSize = view->screen()->size();
	parent->addWidget(widget_2_1_1_1);


	input = new Qt3DInput::QInputAspect;
	view->registerAspect(input);

	// Root entity
	rootEntity = new Qt3DCore::QEntity();

	// Camera
	cameraEntity = view->camera();

	cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	cameraEntity->setPosition(QVector3D(50.0f, 50.0f, 50.0f));// remember : z-axis is facing u from screen
	cameraEntity->setUpVector(QVector3D(-1.0, -1.0, 1.0));
	cameraEntity->setViewCenter(QVector3D(0, 0, 0));

#define dirctionallight
#ifdef env_light
	lightEntity = new Qt3DCore::QEntity(rootEntity);
	light = new Qt3DRender::QEnvironmentLight(lightEntity);
	QUrl tU("file:C:\\Qt\\Qt5.14.0\\Examples\\Qt-5.14.0\\qt3d\\exampleresources\\assets\\cubemaps\\default\\default_irradiance.dds");
	Qt3DRender::QTextureLoader *textureldr = new Qt3DRender::QTextureLoader(lightEntity);
	textureldr->setSource(tU);
	light->setIrradiance(textureldr);
	textureldr->setSource(QUrl("file:C:\\Qt\\Qt5.14.0\\Examples\\Qt-5.14.0\\qt3d\\exampleresources\\assets\\cubemaps\\default\\default_specular.dds"));
	light->setSpecular(textureldr);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

#elif defined(pointlight)
	lightEntity = new Qt3DCore::QEntity(rootEntity);

	Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
	light->setColor("white");
	light->setIntensity(1);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

	//Qt3DRender::QPointLight *light2 = new Qt3DRender::QPointLight(lightEntity);
	//light2->setColor("white");
	//light2->setIntensity(1);
	//lightEntity->addComponent(light2);
	//Qt3DCore::QTransform *lightTransform2 = new Qt3DCore::QTransform(lightEntity);
	//lightTransform2->setTranslation(cameraEntity->position() - QVector3D(cameraEntity->position().x() * 2, 0, 0));
	//lightEntity->addComponent(lightTransform2);

	//Qt3DRender::QPointLight *light3 = new Qt3DRender::QPointLight(lightEntity);
	//light3->setColor("white");
	//light3->setIntensity(1);
	//lightEntity->addComponent(light3);
	//Qt3DCore::QTransform *lightTransform3 = new Qt3DCore::QTransform(lightEntity);
	//lightTransform3->setTranslation(cameraEntity->position() - QVector3D(0,cameraEntity->position().y() * 2, 0));
	//lightEntity->addComponent(lightTransform3);

	//Qt3DRender::QPointLight *light4 = new Qt3DRender::QPointLight(lightEntity);
	//light4->setColor("white");
	//light4->setIntensity(1);
	//lightEntity->addComponent(light4);
	//Qt3DCore::QTransform *lightTransform4 = new Qt3DCore::QTransform(lightEntity);
	//lightTransform4->setTranslation(cameraEntity->position() - QVector3D(0,0,cameraEntity->position().z() * 2));
	//lightEntity->addComponent(lightTransform4);

	//Qt3DRender::QPointLight *light5 = new Qt3DRender::QPointLight(lightEntity);
	//light5->setColor("white");
	//light5->setIntensity(1);
	//lightEntity->addComponent(light5);
	//Qt3DCore::QTransform *lightTransform5 = new Qt3DCore::QTransform(lightEntity);
	//lightTransform5->setTranslation(cameraEntity->position() - QVector3D(cameraEntity->position().x() * 2, cameraEntity->position().y() * 2, 0));
	//lightEntity->addComponent(lightTransform5);

	//Qt3DRender::QPointLight *light6 = new Qt3DRender::QPointLight(lightEntity);
	//light6->setColor("white");
	//light6->setIntensity(1);
	//lightEntity->addComponent(light6);
	//Qt3DCore::QTransform *lightTransform6 = new Qt3DCore::QTransform(lightEntity);
	//lightTransform6->setTranslation(cameraEntity->position() - QVector3D(cameraEntity->position().x() * 2, 0, cameraEntity->position().z() * 2));
	//lightEntity->addComponent(lightTransform6);


#elif defined (dirctionallight)
	lightEntity = new Qt3DCore::QEntity(rootEntity);
	Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
	light->setWorldDirection(QVector3D(1, 0, 0));
	light->setColor("white");
	light->setIntensity(0.5);
	lightEntity->addComponent(light);
	Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
	lightTransform->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform);

	Qt3DRender::QDirectionalLight *light2 = new Qt3DRender::QDirectionalLight(lightEntity);
	light2->setWorldDirection(QVector3D(-1,0,0));
	light2->setColor("white");
	light2->setIntensity(0.5);
	lightEntity->addComponent(light2);
	Qt3DCore::QTransform *lightTransform2 = new Qt3DCore::QTransform(lightEntity);
	lightTransform2->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform2);

	Qt3DRender::QDirectionalLight *light3 = new Qt3DRender::QDirectionalLight(lightEntity);
	light2->setWorldDirection(QVector3D(0, 1, 0));
	light2->setColor("white");
	light2->setIntensity(0.5);
	lightEntity->addComponent(light3);
	Qt3DCore::QTransform *lightTransform3 = new Qt3DCore::QTransform(lightEntity);
	lightTransform3->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform3);

	Qt3DRender::QDirectionalLight *light4 = new Qt3DRender::QDirectionalLight(lightEntity);
	light4->setWorldDirection(QVector3D(0, -1, 0));
	light4->setColor("white");
	light4->setIntensity(0.5);
	lightEntity->addComponent(light4);
	Qt3DCore::QTransform *lightTransform4 = new Qt3DCore::QTransform(lightEntity);
	lightTransform2->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform4);

	Qt3DRender::QDirectionalLight *light5 = new Qt3DRender::QDirectionalLight(lightEntity);
	light5->setWorldDirection(QVector3D(0, 0, 1));
	light5->setColor("white");
	light5->setIntensity(0.5);
	lightEntity->addComponent(light5);
	Qt3DCore::QTransform *lightTransform5 = new Qt3DCore::QTransform(lightEntity);
	lightTransform5->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform5);

	Qt3DRender::QDirectionalLight *light6 = new Qt3DRender::QDirectionalLight(lightEntity);
	light6->setWorldDirection(QVector3D(0, 0, -1));
	light6->setColor("white");
	light6->setIntensity(0.5);
	lightEntity->addComponent(light6);
	Qt3DCore::QTransform *lightTransform6 = new Qt3DCore::QTransform(lightEntity);
	lightTransform6->setTranslation(cameraEntity->position());
	lightEntity->addComponent(lightTransform6);

#endif

	// For camera controls
	Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
	camController->setCamera(cameraEntity);


#pragma endregion

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
	QUrl importobjectURL("file:///D:\\0work\\cpp\\3dp_cpp_opengl\\myQt3D\\myQt3D\\nanosuit.obj");
	//QUrl importobjectURL("file:/D:\\0work\\cpp\\3dp_cpp_opengl\\heartmodel.wrl");
	//QUrl importobjectURL("file:/D:\\0work\\cpp\\3dp_cpp_opengl\\Gorld3D\\Gorld3D\\Gorld3D\\toyplane.obj");
	m_importSceneLoader->setSource(importobjectURL);
	Qt3DRender::QMesh *meshimport = new Qt3DRender::QMesh();
	meshimport->setSource(QUrl("file:/D:\\0work\\cpp\\3dp_cpp_opengl\\Gorld3D\\Gorld3D\\Gorld3D\\gear.stl"));
	//! [1]设置变换component
	Qt3DCore::QTransform *importTransform = new Qt3DCore::QTransform();
	importTransform->setScale(0.1f);
	importTransform->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0f, 0.0f, 0.0f), 25.0f));
	importTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
	//! [1]

	////! [2]设置材质
	Qt3DExtras::QPhongMaterial *importMaterial = new Qt3DExtras::QPhongMaterial();
	//importMaterial->setDiffuse(QColor(qRgba(0.8,0.8,0.8,1))); displayed black object for unknown reason
	importMaterial->setAmbient(QColor(qRgba(0.6, 0.2, 0.1, 1)));
	importMaterial->setSpecular(QColor(qRgba(0.2, 0.9, 0.1, 1)));
	importMaterial->setShininess(0.6f);
	////! [2]

	//! [3]加载各component到根实体（entity/node）
	m_importEntity->addComponent(m_importSceneLoader);
	//m_importEntity->addComponent(meshimport);
	m_importEntity->addComponent(importMaterial);
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

bool Scene3d::slot_test()
{
	if (lightEntity != Q_NULLPTR)
	{
	delete  lightEntity;
	lightEntity = Q_NULLPTR;
	}
	else
	{
		lightEntity = new Qt3DCore::QEntity(rootEntity);
		Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
		light->setWorldDirection(QVector3D(1, 0, 0));
		light->setColor("white");
		light->setIntensity(0.5);
		lightEntity->addComponent(light);
		Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
		lightTransform->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform);

		Qt3DRender::QDirectionalLight *light2 = new Qt3DRender::QDirectionalLight(lightEntity);
		light2->setWorldDirection(QVector3D(-1, 0, 0));
		light2->setColor("white");
		light2->setIntensity(0.5);
		lightEntity->addComponent(light2);
		Qt3DCore::QTransform *lightTransform2 = new Qt3DCore::QTransform(lightEntity);
		lightTransform2->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform2);

		Qt3DRender::QDirectionalLight *light3 = new Qt3DRender::QDirectionalLight(lightEntity);
		light2->setWorldDirection(QVector3D(0, 1, 0));
		light2->setColor("white");
		light2->setIntensity(0.5);
		lightEntity->addComponent(light3);
		Qt3DCore::QTransform *lightTransform3 = new Qt3DCore::QTransform(lightEntity);
		lightTransform3->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform3);

		Qt3DRender::QDirectionalLight *light4 = new Qt3DRender::QDirectionalLight(lightEntity);
		light4->setWorldDirection(QVector3D(0, -1, 0));
		light4->setColor("white");
		light4->setIntensity(0.5);
		lightEntity->addComponent(light4);
		Qt3DCore::QTransform *lightTransform4 = new Qt3DCore::QTransform(lightEntity);
		lightTransform2->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform4);

		Qt3DRender::QDirectionalLight *light5 = new Qt3DRender::QDirectionalLight(lightEntity);
		light5->setWorldDirection(QVector3D(0, 0, 1));
		light5->setColor("white");
		light5->setIntensity(0.5);
		lightEntity->addComponent(light5);
		Qt3DCore::QTransform *lightTransform5 = new Qt3DCore::QTransform(lightEntity);
		lightTransform5->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform5);

		Qt3DRender::QDirectionalLight *light6 = new Qt3DRender::QDirectionalLight(lightEntity);
		light6->setWorldDirection(QVector3D(0, 0, -1));
		light6->setColor("white");
		light6->setIntensity(0.5);
		lightEntity->addComponent(light6);
		Qt3DCore::QTransform *lightTransform6 = new Qt3DCore::QTransform(lightEntity);
		lightTransform6->setTranslation(cameraEntity->position());
		lightEntity->addComponent(lightTransform6);

	}
	return true;
}