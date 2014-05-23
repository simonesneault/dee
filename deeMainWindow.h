#ifndef deeMainWindow_H
#define deeMainWindow_H

#include <QWidget>

namespace dee{

	class Viewer;
	class MainWindow : public QWidget{
		
		Q_OBJECT

	protected:
		
		Viewer* m_viewer;		
		
	public:
		MainWindow( QWidget* a_parent=NULL );
		virtual ~MainWindow();
		
	};
}

#endif //deeMainWindow_H