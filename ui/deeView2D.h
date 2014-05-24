#ifndef DEE_VIEW_2D_H
#define DEE_VIEW_2D_H

#include "deeView.h"

namespace dee{
	class View2D : public View{

		Q_OBJECT

	protected:
		vtkResliceImageViewer* m_reslice_image_viewer;
		int                    m_plane_orientation;
		bool                   m_plane_oblique;

	public:
		View2D( QWidget* a_parent = NULL );
		virtual ~View2D();

		virtual void setImageData( vtkImageData* );
		virtual void init();

		void setPlaneOrientation( int );
		int getPlaneOrientation();

		void setPlaneOblique( bool );
		bool getPlaneOblique();

		void setWindow( double );
		double getWindow();

		void setLevel( double );
		double getLevel();
	};
}

#endif
