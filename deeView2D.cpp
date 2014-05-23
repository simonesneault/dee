#include "deeView2D.h"

#include "vtkResliceImageViewer.h"
#include "vtkRenderWindow.h"

namespace dee{
	View2D::View2D( QWidget* a_parent ):View( a_parent ){
		m_volume = NULL;
		m_reslice_image_viewer = vtkResliceImageViewer::New();
		m_reslice_image_viewer->SetResliceModeToAxisAligned();
	}
	
	View2D::~View2D(){
		m_reslice_image_viewer->Delete();
	}


	void View2D::setVolume( vtkImageData* a_volume ){
		
		m_volume = a_volume;
		Q_ASSERT( m_volume );

		this->init();
		m_reslice_image_viewer->SetInputData( a_volume );
	}

	void View2D::init(){
		if( m_is_init )
			return;
		m_is_init = true;
		m_reslice_image_viewer->SetupInteractor( this->GetRenderWindow()->GetInteractor() );
		this->SetRenderWindow( m_reslice_image_viewer->GetRenderWindow() );
	}

	void View2D::setPlaneOrientation( int a ){
		m_reslice_image_viewer->SetSliceOrientation( a );
	}

	int View2D::getPlaneOrientation(){
		return m_reslice_image_viewer->GetSliceOrientation();
	}


}