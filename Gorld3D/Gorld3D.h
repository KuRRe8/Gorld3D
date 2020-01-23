#pragma once

#include "__Utilities.h"
#include <QtWidgets/QMainWindow>
#include "ui_Gorld3D.h"

class Gorld3D : public QMainWindow
{
	Q_OBJECT

public:
	Gorld3D(QWidget *parent = Q_NULLPTR);
	~Gorld3D();

private:
	Ui::Gorld3DClass ui;
};
