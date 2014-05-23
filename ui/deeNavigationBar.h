#ifndef DEE_NAVIGATION_BAR_H
#define DEE_NAVIGATION_BAR_H

#include <QWidget>

namespace dee{

	class NavigationBar : public QWidget{
		
		Q_OBJECT
		
	protected:
		
	public:
		NavigationBar( QWidget* a_parent=NULL );
		virtual ~NavigationBar();
	
	signals:
		void goToPatientManager();
		void goToViewer();
		void goToReport();
	};
	
}

#endif