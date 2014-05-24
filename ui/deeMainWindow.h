#ifndef DEE_MAIN_WINDOW_H
#define DEE_MAIN_WINDOW_H

#include "deeCore.h"

namespace dee{

	class Viewer;
	class MainWindow : public QWidget{
		
		Q_OBJECT

	protected:
		
		Viewer*      m_viewer;		
	public:
		MainWindow( QWidget* a_parent=NULL );
		virtual ~MainWindow();
		
	};
}

#endif