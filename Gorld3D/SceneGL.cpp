#include "SceneGL.h"
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMouseEvent>

GLWidget::GLWidget(QWidget *parent)
	: QOpenGLWidget(parent),
	clearColor(Qt::white),
	xRot(0),
	yRot(0),
	zRot(0),
	program(0)
{
	//memset(textures, 0, sizeof(textures));
	qtimer = new QTimer();
	connect(qtimer, SIGNAL(timeout()), this, SLOT(updatenearplane()));
}

GLWidget::~GLWidget()
{
	makeCurrent();
	vbo->destroy();
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

void GLWidget::updatenearplane()
{
	nearplane += 2.0f;
	update();
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

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	makeObject();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glEnable(GL_CULL_FACE);

	QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char *vsrc =
		"attribute highp vec4 vertex;\n"
		//"attribute mediump vec4 texCoord;\n"
		//"varying mediump vec4 texc;\n"
		"attribute mediump vec4 colors;\n"
		"varying mediump vec4 colorv;\n"
		"uniform mediump mat4 matrix;\n"
		"void main(void)\n"
		"{\n"
		"    gl_Position = matrix * vertex;\n"
		"	 colorv = colors;\n"
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
	QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char *fsrc =
		//"uniform sampler2D texture;\n"
		//"varying mediump vec4 texc;\n"
		"varying mediump vec4 colorv;\n"
		"void main(void)\n"
		"{\n"
		//"    gl_FragColor = vec4(0.1,0.6,0.7,1.0); \n"
		"	 gl_FragColor = colorv;\n"
		"}\n";
		//"#version 330 core\n"
		//"out vec4 FragColor;\n"

		//"void main()\n"
		//"{\n"
		//"FragColor = vec4(0.5,0.6,0.7,0.8);\n"
		//"}\n";

	fshader->compileSourceCode(fsrc);

	program = new QOpenGLShaderProgram;
	program->addShader(vshader);
	program->addShader(fshader);
	program->bindAttributeLocation("vertex", 0);
	//program->bindAttributeLocation("texCoord", 1);
	program->bindAttributeLocation("colors", 1);
	program->link();
	program->bind();
	//program->setUniformValue("texture", 0);

	sliceFbo = new QOpenGLFramebufferObject(QSize(800, 600));
	sliceFbo->setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

	nearplane = -50.0f;
	qtimer->start(100);
}


void GLWidget::makeObject()
{
	model3mf = new Model3MF("model/colorcube.3mf");

	vao.create();
	vao.bind();

		vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
		vbo->create();
		vbo->bind();

		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		vbo->allocate(model3mf->newvertices.constData(), model3mf->newvertices.count() * 4);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat) + 4 * sizeof(uint), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_INT, GL_TRUE, 3 * sizeof(GLfloat) + 4 * sizeof(uint), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		vbo->release();
		ebo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
		ebo->create();
		ebo->bind();
		ebo->allocate(model3mf->indices.constData(), model3mf->indices.count() * sizeof(quint32));
		ebo->release();
	vao.release();
}

void GLWidget::paintGL()
{
	glClearColor(clearColor.redF(), clearColor.greenF(), clearColor.blueF(), clearColor.alphaF());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear color and depth since depth test enabled. when stencil used,clear the stencilbuffer too
 	////glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF); //keep intact

	QMatrix4x4 m;
	m.ortho(model3mf->modelmin,model3mf->modelmax, model3mf->modelmin, model3mf->modelmax, model3mf->modelmin, model3mf->modelmax);
	m.translate(100.0f, 100.0f, -1*model3mf->zmax);
	m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
	m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
	m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
	program->setUniformValue("matrix", m);

	vao.bind();
		ebo->bind();

		////glEnable(GL_CULL_FACE);
		////glCullFace(GL_FRONT);
		////glStencilFunc(GL_ALWAYS, 0, 0xff);
		////glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		////glDrawArrays(GL_TRIANGLES, 0, model3mf->indices.count());

		////glCullFace(GL_BACK);
		////glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
		////glDrawArrays(GL_TRIANGLES, 0, model3mf->indices.count());
		////glDisable(GL_CULL_FACE);
		////glClear(GL_COLOR_BUFFER_BIT);

		////glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
		////glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		///glDrawElements(GL_TRIANGLES, model3mf->indices.count(), GL_UNSIGNED_INT, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, model3mf->indices.count());
		////glDisable(GL_CULL_FACE);
		////glDisable(GL_STENCIL_TEST);
		ebo->release();
	vao.release();
}

void GLWidget::renderSlice()
{
	//sliceFbo->bind();
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glStencilFunc(GL_ALWAYS, 0, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	//	self.gl.glDrawArrays(self.gl.GL_TRIANGLES, 0, self.numOfVerts)

	//	self.gl.glCullFace(self.gl.GL_BACK)
	//	self.gl.glStencilOp(self.gl.GL_KEEP, self.gl.GL_KEEP, self.gl.GL_DECR)
	//	self.gl.glDrawArrays(self.gl.GL_TRIANGLES, 0, self.numOfVerts)
	//	self.gl.glDisable(self.gl.GL_CULL_FACE)

	//	self.gl.glClear(self.gl.GL_COLOR_BUFFER_BIT)
	//	self.maskVAO.bind()
	//	self.gl.glStencilFunc(self.gl.GL_NOTEQUAL, 0, 0xFF)
	//	self.gl.glStencilOp(self.gl.GL_KEEP, self.gl.GL_KEEP, self.gl.GL_KEEP)
	//	self.gl.glDrawArrays(self.gl.GL_TRIANGLES, 0, 6)
	//	self.gl.glDisable(self.gl.GL_STENCIL_TEST)

	//	image = self.sliceFbo.toImage()
	//	# makes a QComboBox for different Image Format,
	//	# namely Format_Mono, Format_MonoLSB, and Format_Grayscale8
	//	image = image.convertToFormat(QtGui.QImage.Format_Grayscale8)
	//	image.save(os.path.join(self.sliceSavePath,
	//		'out{:04d}.png'.format(self.currentLayer)))
	//	self.sliceFbo.release()
}
