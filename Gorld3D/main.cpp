#include "Gorld3D.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Gorld3D w;
	w.show();
	return a.exec();
}
