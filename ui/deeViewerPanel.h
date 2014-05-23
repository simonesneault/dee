#ifndef DEE_VIEWER_PANEL_H
#define DEE_VIEWER_PANEL_H

#include <QWidget>

namespace dee{

	class ViewerPanel : public QWidget{
		
		Q_OBJECT
		
	protected:

	public:
		ViewerPanel( QWidget* a_parent=NULL );
		virtual ~ViewerPanel();
	
	};
}

#endif