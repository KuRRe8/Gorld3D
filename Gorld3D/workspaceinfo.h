#pragma once

#include <QWidget>
#include "ui_workspaceinfo.h"

class workspaceinfo : public QWidget
{
	Q_OBJECT

public:
	workspaceinfo(QWidget *parent = Q_NULLPTR);
	~workspaceinfo();

private:
	Ui::workspaceinfo ui;
};
