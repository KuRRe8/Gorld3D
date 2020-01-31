#pragma once

#include "__Utilities.h"
#include "ui_SettingDlg.h"

class SettingDlg : public QWidget
{
	Q_OBJECT

public:
	SettingDlg(QWidget *parent = Q_NULLPTR);
	~SettingDlg();

private:
	Ui::SettingDlg ui;
};
