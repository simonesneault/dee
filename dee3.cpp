#include <QApplication>

#include "deeMainWindow.h"

int main( int a_argc, char** a_argv ){
	QApplication l_app( a_argc, a_argv );

	deeMainWindow l_main( a_argc, a_argv );
	l_main.show();

	return l_app.exec();
}
