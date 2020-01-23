#include "Gorld3D.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication protogonus(argc, argv);
	Gorld3D w;
	w.show();
	return protogonus.exec();
}
