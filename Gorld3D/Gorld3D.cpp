#include "Gorld3D.h"

Gorld3D::Gorld3D(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	UI_Construction();
	Retranslate();
	Connection_Arrangement();
}

Gorld3D::~Gorld3D()
{
	logger_tag = "Gorld3D";
	log_i("instance exiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiit\n\n");
}

void Gorld3D::UI_Construction()
{
	QHBoxLayout* hboxlayout_2_1_1_ = new QHBoxLayout(ui.widget_2_1_3DviewContainer);
	//stackedlayout_2_1_1_->setStackingMode(QStackedLayout::StackAll);
	transparentandtools = new TransparentAndTools(hboxlayout_2_1_1_);
	s3d = new Scene3d(hboxlayout_2_1_1_);
	ui.widget_2_1_3DviewContainer->setLayout(hboxlayout_2_1_1_);

	ui.stackedWidget->removeWidget(ui.page_5);
	ui.stackedWidget->removeWidget(ui.page_6);// in .ui I just cant make a null stackedwidget
	infobuttoncontainer_index = 1; //default to jobinfo tab, ui.stackedWidget->setCurrentIndex(infobuttoncontainer_index - 1)
	workinfotab = new workspaceinfo(this);
	ui.stackedWidget->addWidget(workinfotab);
	ui.stackedWidget->setCurrentIndex(infobuttoncontainer_index - 1);
	

}

void Gorld3D::Retranslate()
{

}

void Gorld3D::Connection_Arrangement()
{

}

void Gorld3D::on_actionAbout_triggered()
{
	QMessageBox::about(this, QStringLiteral("ABOUT GORLD 3D"),QStringLiteral(""));
}

void Gorld3D::on_actionSettings_triggered()
{
	//settingDlg = new SettingDlg(this);
	//settingDlg->show();
}

void Gorld3D::on_actionAdd_Components_triggered()
{
	QFileDialog* filedlg = new QFileDialog(this);
	filedlg->setAttribute(Qt::WA_DeleteOnClose);
	filedlg->resize(QSize(800, 600));
	filedlg->show();
}

void Gorld3D::on_actiontest_btn_triggered()
{
	s3d->slot_test();
}

void Gorld3D::on_pushButton_1_1_4_settings_released()
{
	settingDlg->show();
}

void Gorld3D::on_jobinfo_pushButton_released()
{
	if (infobuttoncontainer_index == 1)
	{
		ui.jobinfo_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(240,240,240);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(229,241,251);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		infobuttoncontainer_index = 0;
		ui.stackedWidget->hide();
	}
	else
	{
		ui.jobinfo_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(119, 185, 252);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(119, 185, 252);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		quint8 last_infobuttoncontainer_index = infobuttoncontainer_index;
		infobuttoncontainer_index = 1;
		ui.stackedWidget->setCurrentIndex(infobuttoncontainer_index - 1);
		if (last_infobuttoncontainer_index == 0)
		{
			ui.stackedWidget->show();
		}
	}
}

void Gorld3D::on_components_pushButton_released()
{
	if (infobuttoncontainer_index == 2)
	{
		ui.components_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(240,240,240);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(229,241,251);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		infobuttoncontainer_index = 0;
		ui.stackedWidget->hide();
	}
	else
	{
		ui.components_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(119, 185, 252);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(119, 185, 252);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		quint8 last_infobuttoncontainer_index = infobuttoncontainer_index;
		infobuttoncontainer_index = 2;
		ui.stackedWidget->setCurrentIndex(infobuttoncontainer_index - 1);
		if (last_infobuttoncontainer_index == 0)
		{
			ui.stackedWidget->show();
		}
	}
}

void Gorld3D::on_scenesetting_pushButton_released()
{
	if (infobuttoncontainer_index == 3)
	{
		ui.scenesetting_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(240,240,240);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(229,241,251);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		infobuttoncontainer_index = 0;
		ui.stackedWidget->hide();
	}
	else
	{
		ui.scenesetting_pushButton->setStyleSheet(QString::fromUtf8("QPushButton{background-color:rgb(119, 185, 252);\n"
			"color: white;\n"
			"/*border-radius:10px;\n"
			"border: 2px groove gray;*/\n"
			"border-style: outset;}\n"
			"QPushButton:hover{background-color:rgb(119, 185, 252);\n"
			"color: black;}\n"
			"QPushButton:pressed{background-color:rgb(119, 185, 252);}\n"
			""));
		quint8 last_infobuttoncontainer_index = infobuttoncontainer_index;
		infobuttoncontainer_index = 3;
		ui.stackedWidget->setCurrentIndex(infobuttoncontainer_index - 1);
		if (last_infobuttoncontainer_index == 0)
		{
			ui.stackedWidget->show();
		}
		else
		{

		}
	}
}
