#include "deeView2D.h"

#include "vtkImageData.h"
#include "vtkResliceImageViewer.h"
#include "vtkRenderWindow.h"

namespace dee{
	View2D::View2D( QWidget* a_parent ):View( a_parent ){
		m_volume = NULL;
		m_reslice_image_viewer = vtkResliceImageViewer::New();
		m_reslice_image_viewer->SetResliceModeToAxisAligned();
		m_plane_orientation = 0;
		m_plane_oblique = false;
	}
	
	View2D::~View2D(){
		m_reslice_image_viewer->Delete();
	}


	void View2D::setVolume( vtkImageData* a_volume ){
		
		m_volume = a_volume;
		Q_ASSERT( m_volume );

		this->init();
		m_reslice_image_viewer->SetInputData( a_volume );
		m_reslice_image_viewer->SetSliceOrientation( m_plane_orientation );
		m_reslice_image_viewer->SetSlice( m_volume->GetDimensions()[m_plane_orientation]/2 );
		m_reslice_image_viewer->Render();
	}

	void View2D::init(){
		if( m_is_init )
			return;
		m_is_init = true;
		m_reslice_image_viewer->SetupInteractor( this->GetRenderWindow()->GetInteractor() );
		this->SetRenderWindow( m_reslice_image_viewer->GetRenderWindow() );
		
	}

	void View2D::setPlaneOrientation( int a ){
		m_plane_orientation = a;
	}

	int View2D::getPlaneOrientation(){
		return m_reslice_image_viewer->GetSliceOrientation();
	}
	
	void View2D::setPlaneOblique( bool a ){
		m_plane_oblique = a;
		if( m_plane_oblique )
			m_reslice_image_viewer->SetResliceModeToOblique();
		else
			m_reslice_image_viewer->SetResliceModeToAxisAligned();
	}

	bool View2D::getPlaneOblique(){
		return ( m_reslice_image_viewer->GetResliceMode() == 1 );
	}

}