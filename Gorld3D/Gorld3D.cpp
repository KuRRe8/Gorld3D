#include "Gorld3D.h"

Gorld3D::Gorld3D(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Gorld3D::~Gorld3D()
{
	logger_tag = "Gorld3D";
	log_i("instance exit");
}