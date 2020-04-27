#pragma once
#include "__Utilities.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "3mfLoader.h"


QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram);
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit GLWidget(QWidget *parent = 0);
	~GLWidget();

	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	void rotateBy(int xAngle, int yAngle, int zAngle);
	void setClearColor(const QColor &color);

signals:
	void clicked();

protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;

private:
	void makeObject();

	QColor clearColor;
	QPoint lastPos;
	int xRot;
	int yRot;
	int zRot;
	//QOpenGLTexture *textures[6];
	QOpenGLShaderProgram *program;
	QOpenGLBuffer* vbo;
	QOpenGLVertexArrayObject vao;
	QOpenGLBuffer* ebo;
	Model3MF* model3mf;
};
