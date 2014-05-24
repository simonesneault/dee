#include <QApplication>

#include "core/deeCore.h"
#include "ui/deeMainWindow.h"

int main( int a_argc, char** a_argv ){
	QApplication l_app( a_argc, a_argv );

	// start main engine
	dee::Core::Engine().Start( &l_app );
	dee::MainWindow l_dee;
	l_dee.show();

	return l_app.exec();
}
