#pragma once
/*
main window of app. 
*/
#include "__Utilities.h"
#include <qsplashscreen.h>
#include "qstackedlayout.h"
#include "Scene3d.h"
#include "SceneGL.h"
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
	Scene3d* scene3d;
	GLWidget* sceneGL;
	SettingDlg* settingDlg;
	TransparentAndTools* transparentandtools;
	workspaceinfo* workinfotab;
	quint8 infobuttoncontainer_index; //0: none  1: jobinfo  2: components  3: scenesetting
	
signals:
	;

private slots:
	void on_actiontest_btn_triggered();
	void on_actionAbout_triggered();
	void on_actionSettings_triggered();
	void on_actionAdd_Components_triggered();
	void on_pushButton_1_1_4_settings_released();
	void on_jobinfo_pushButton_released();
	void on_components_pushButton_released();
	void on_scenesetting_pushButton_released();
};
