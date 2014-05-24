#include <QApplication>

#include "core/deeCore.h"
#include "ui/deeMainWindow.h"

int main( int a_argc, char** a_argv ){
	// start Qt application
	QApplication l_app( a_argc, a_argv );

	// display splash screen	
	QSplashScreen l_splash( l_app.applicationDirPath() + "/data/dee_splash.png" );
	l_splash.show();
	l_app.processEvents();

	// start main engine
	dee::Core::Engine().Start( &l_app );
	dee::MainWindow l_dee;
	l_dee.show();
	l_splash.finish( &l_dee );

	return l_app.exec();
}
