#include "deeView3D.h"

namespace dee{
	View3D::View3D( QWidget* a_parent ) : View( a_parent ){
	
	}
	
	View3D::~View3D(){
	
	}

	
	void View3D::setVolume( vtkImageData* a_volume ){
		
		m_volume = a_volume;
		Q_ASSERT( m_volume );

		this->init();
	}

	void View3D::init(){
		if( m_is_init )
			return;
		m_is_init = true;
		
	}

}