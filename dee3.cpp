#include <QApplication>

#include "deeMainWindow.h"

int main( int a_argc, char** a_argv ){
	QApplication l_app( a_argc, a_argv );

	dee::MainWindow l_dee;
	l_dee.show();

	return l_app.exec();
}
