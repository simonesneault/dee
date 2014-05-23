#ifndef deeView2D_H
#define deeView2D_H

#include "deeView.h"

class vtkResliceImageViewer;

namespace dee{
	class View2D : public View{

		Q_OBJECT

	protected:
		vtkResliceImageViewer * m_reslice_image_viewer;

	public:
		View2D( QWidget* a_parent = NULL );
		virtual ~View2D();

		virtual void setVolume( vtkImageData* );
		virtual void init();

		void setPlaneOrientation( int );
		int getPlaneOrientation();
	};
}

#endif // deeView2D_H
