/*
This flie contains some useful functions, as well as __Definitions.h&__GlobalVars.h
Also including most popular qxxxx.h
*/

#pragma once
#include "__GlobalVars.h"
#include "qmessagebox.h"
#include "3rdparty\elog.h"
#include "qtextcodec.h"
#include "qtranslator.h"
#include "qscreen.h"
#include <qstringliteral.h>	//accelerate runtime processing, convert const char* 2 QString at compiletime
#include <QWidget>
#include <Windows.h>
#include <csignal>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>

//get mainwindow pointer utility, use forceinline to get LV.1 warning when O2 optimization cannot do inline opt.
__forceinline QMainWindow* getMainWindow()
{
	foreach(QWidget *w, qApp->topLevelWidgets())
		if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
			return mainWin;
	return nullptr;
}
