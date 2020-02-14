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

	workinfotab = new workspaceinfo(this);
	ui.stackedWidget->addWidget(workinfotab);
	ui.stackedWidget->setCurrentIndex(0);
	int a = ui.stackedWidget->currentIndex();

	
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
}
