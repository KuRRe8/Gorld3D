#pragma once
/*
main window of app. 
*/
#include "__Utilities.h"
#include <qsplashscreen.h>
#include "qstackedlayout.h"
#include "Scene3d.h"
#include "SettingDlg.h"
#include "qfiledialog.h"
#include "TransparentAndTools.h"
#include "workspaceinfo.h"
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
	TransparentAndTools* transparentandtools;
	workspaceinfo* workinfotab;
	
signals:
	;

private slots:
	void on_actiontest_btn_triggered();
	void on_actionAbout_triggered();
	void on_actionSettings_triggered();
	void on_actionAdd_Components_triggered();
};
