#include "deeView.h"

namespace dee{
	View::View( QWidget* a_parent ) : QVTKWidget( a_parent ){
		m_image_data = NULL;
		m_is_init = false;
	}
	
	View::~View(){
	
	}

	void View::setStringId( const QString& a ){
		m_string_id = a;
	}
	
	const QString& View::getStringId(){
		return m_string_id;
	}

	
	void View::setImageData( vtkImageData* a_image_data ){
		Q_ASSERT( a_image_data );
		m_image_data = a_image_data;
	}

	vtkImageData* View::getImageData(){
		return m_image_data;
	}

	bool View::isInit(){
		return m_is_init;
	}

}