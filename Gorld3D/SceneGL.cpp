#include "SceneGL.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	clearColor(Qt::black),
	xRot(0),
	yRot(0),
	zRot(0),
	program(0)
{
	//memset(textures, 0, sizeof(textures));
}

GLWidget::~GLWidget()
{
	makeCurrent();
	vbo->destroy();
	//for (int i = 0; i < 6; ++i)
		//delete textures[i];
	delete program;
	doneCurrent();
}

QSize GLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
	return QSize(200, 200);
}

void GLWidget::rotateBy(int xAngle, int yAngle, int zAngle)
{
	xRot += xAngle;
	yRot += yAngle;
	zRot += zAngle;
	update();
}

void GLWidget::setClearColor(const QColor &color)
{
	clearColor = color;
	update();
}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	//context()->versionFunctions();
	makeObject();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
#define PROGRAM_VERTEX_ATTRIBUTE 0
//#define PROGRAM_TEXCOORD_ATTRIBUTE 1
	//QOpenGLShaderProgram *vs = new QOpenGLShaderProgram();
	//vs->create();
	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute highp vec4 vertex;\n"
		//"attribute mediump vec4 texCoord;\n"
		//"varying mediump vec4 texc;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = matrix * vertex;\n"
		//"    texc = texCoord;\n"
		"}\n";
		////"#version 330 core\n"
		////"layout(location = 0) in vec3 vert;\n"
		//////"uniform mat4 model;"
		//////"uniform mat4 proj;"
		////"uniform mediump mat4 matrix;\n"
		////"void main() {\n"
		////"gl_Position =matrix*vec4(vert,1.0f);\n"
		////"}\n";

	vshader->compileSourceCode(vsrc);
	//vs->addShaderFromSourceCode(QOpenGLShader::Vertex, vsrc);
	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	//QOpenGLShaderProgram* fs = new qopengl
	const char *fsrc =
		//"uniform sampler2D texture;\n"
		//"varying mediump vec4 texc;\n"
		"void main(void)\n"
		"{\n"
		"    gl_FragColor = vec4(0.1,0.5,0.1, 1.0); \n"
		"}\n";
		//"#version 330 core\n"
		//"out vec4 FragColor;\n"

		//"void main()\n"
		//"{\n"
		//"FragColor = vec4(0.5);\n"
		//"}\n";

	fshader->compileSourceCode(fsrc);

	program = new QOpenGLShaderProgram;
	program->addShader(vshader);
	program->addShader(fshader);
	program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
	//program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
	program->link();
	program->bind();
	//program->setUniformValue("texture", 0);
}

void GLWidget::paintGL()
{
	glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	QMatrix4x4 m;
	m.ortho(-500.5f, +500.5f, +500.5f, -500.5f,-500.0f, 500.0f);
	//m.translate(-0.1f, -0.1f, -1.0f);
	m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
	m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
	m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
	program->setUniformValue("matrix", m);

	vao.bind();
//program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
	//program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
	//program->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
	//program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

	//for (int i = 0; i < 6; ++i) {
	//	textures[i]->bind();
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
	//}
	ebo->bind();
	glDrawElements(GL_TRIANGLES,model3mf->indices.count(), GL_UNSIGNED_INT,(void*)0);
	for (int i = 0; i < 6; ++i) {
		//glDrawArrays(GL_TRIANGLES, i * 4, 4);
	}
	ebo->release();
	vao.release();

}
void GLWidget::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		rotateBy(8 * dy, 8 * dx, 0);
	}
	else if (event->buttons() & Qt::RightButton) {
		rotateBy(8 * dy, 0, 8 * dx);
	}
	lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
	emit clicked();
}

void GLWidget::makeObject()
{
	model3mf = new Model3MF("ttj.3mf");
	vao.create();
	vao.bind();
	vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbo->create();
	vbo->bind();
	   
	QVector<float> tempvertices;
	tempvertices.push_back(0.0f);
	tempvertices.push_back(40.0f);
	tempvertices.push_back(40.0f);
	tempvertices.push_back(40.0f);
	tempvertices.push_back(40.0f);
	tempvertices.push_back(40.0f);
	tempvertices.push_back(0.0f);
	tempvertices.push_back(80.0f);
	tempvertices.push_back(40.0f);

	tempvertices.push_back(+1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(-1.2f);
	tempvertices.push_back(+1.2f);
	tempvertices.push_back(-1.2f);

	QVector<quint32> tempindices;
	tempindices.push_back(0);
	tempindices.push_back(1);
	tempindices.push_back(2);
	tempindices.push_back(3);
	tempindices.push_back(4);
	tempindices.push_back(5);
	//tempindices.push_back(6);
	//tempindices.push_back(7);
	//tempindices.push_back(8);
	//tempindices.push_back(9);
	//tempindices.push_back(10);
	//tempindices.push_back(11);
	static const int coords[6][4][3] = {
		{ { +1, -1, -1 },{ -1, -1, -1 },{ -1, +1, -1 },{ +1, +1, -1 } },
		{ { +1, +1, -1 },{ -1, +1, -1 },{ -1, +1, +1 },{ +1, +1, +1 } },
		{ { +1, -1, +1 },{ +1, -1, -1 },{ +1, +1, -1 },{ +1, +1, +1 } },
		{ { -1, -1, -1 },{ -1, -1, +1 },{ -1, +1, +1 },{ -1, +1, -1 } },
		{ { +1, -1, +1 },{ -1, -1, +1 },{ -1, -1, -1 },{ +1, -1, -1 } },
		{ { -1, -1, +1 },{ +1, -1, +1 },{ +1, +1, +1 },{ -1, +1, +1 } }
	};

	QVector<GLfloat> vertData;
	for (int i = 0; i < 6; ++i) {
		for (int j = 0; j < 4; ++j) {
			// vertex position
			vertData.append(0.2 * coords[i][j][0]);
			vertData.append(0.2 * coords[i][j][1]);
			vertData.append(0.2 * coords[i][j][2]);
		}
	}

	vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo->allocate(model3mf->vertices.constData(), model3mf->vertices.count() * sizeof(GLfloat));
//	vbo->allocate(tempvertices.constData(), tempvertices.count() * sizeof(GLfloat));

	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),0);
	glEnableVertexAttribArray(0);

	vbo->release();
	ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	ebo->create();
	ebo->bind();
	ebo->allocate(model3mf->indices.constData(), model3mf->indices.count() * sizeof(quint32));
	//ebo->allocate(tempindices.constData(), tempindices.count() * sizeof(quint32));
	ebo->release();
	vao.release();
}
