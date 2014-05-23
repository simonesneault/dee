#include "deeView.h"

namespace dee{
	View::View( QWidget* a_parent ) : QVTKWidget( a_parent ){
		m_volume = NULL;
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

	
	void View::setVolume( vtkImageData* a_volume ){
		Q_ASSERT( a_volume );
		m_volume = a_volume;
	}

	vtkImageData* View::getVolume(){
		return m_volume;
	}

	bool View::isInit(){
		return m_is_init;
	}

}