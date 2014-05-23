#ifndef deeViewer_H
#define deeViewer_H

#include <QWidget>

class vtkImageData;

namespace dee{
	class View;

	class Viewer : public QWidget{
		
		Q_OBJECT
		
		QVector<View*> m_views;
		vtkImageData* m_volume;

	public:
		Viewer( QWidget* a_parent=NULL );
		virtual ~Viewer();
		
		View* getView( const QString& a_id );

		void setVolume( vtkImageData* );
		vtkImageData* getVolume();

	public slots:
		void onOpenVolumeButton(); 
	};
}

#endif //deeViewer_H