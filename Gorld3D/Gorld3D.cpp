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
	QStackedLayout* stackedlayout_2_1_1_ = new QStackedLayout(ui.widget_2_1_3DviewContainer);
	stackedlayout_2_1_1_->setStackingMode(QStackedLayout::StackAll);
	s3d = new Scene3d(stackedlayout_2_1_1_);
	ui.widget_2_1_3DviewContainer->setLayout(stackedlayout_2_1_1_);


}

void Gorld3D::Retranslate()
{

}

void Gorld3D::Connection_Arrangement()
{

}

void Gorld3D::on_actionAbout_triggered()
{
	QMessageBox::about(this, QStringLiteral("ABOUT GORLD 3D"), QStringLiteral("This is an expiremental ver.  VER0.02"));
}

void Gorld3D::on_actionSettings_triggered()
{
	//settingDlg = new SettingDlg(this);
	//settingDlg->show();
}

void Gorld3D::on_actionAdd_Components_triggered()
{
	QFileDialog* filedlg = new QFileDialog(this);
	filedlg->show();
}

void Gorld3D::on_actiontest_btn_triggered()
{
}
