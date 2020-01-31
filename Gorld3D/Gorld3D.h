#pragma once
/*
main window of app. 
*/
#include "__Utilities.h"
#include <QtWidgets/QMainWindow>
#include <qsplashscreen.h>
#include "qstackedlayout.h"
#include "Scene3d.h"
#include "SettingDlg.h"
#include "qfiledialog.h"

#include "ui_Gorld3D.h"

class Gorld3D : public QMainWindow
{
	Q_OBJECT

public:
	Gorld3D(QWidget *parent = Q_NULLPTR);
	~Gorld3D();

private:
	Ui::Gorld3DClass ui;
	void UI_Construction();
	void Retranslate();
	void Connection_Arrangement();
	Scene3d* s3d;
	SettingDlg* settingDlg;
signals:
	;

private slots:
	void on_actiontest_btn_triggered();
	void on_actionAbout_triggered();
	void on_actionSettings_triggered();
	void on_actionAdd_Components_triggered();
};
