#include "deeViewer.h"

#include "deeView2D.h"
#include "deeView3D.h"

#include <QtWidgets>

#include "vtkImageData.h"
#include "vtkImageReader.h"
#include "vtkDICOMImageReader.h"

namespace dee{
	Viewer::Viewer( QWidget* a_parent /*=NULL*/ ){

		// build 3 2D views
	
		View2D* l_axial_view = new View2D( this );
		View2D* l_sagit_view = new View2D( this );
		View2D* l_coro_view  = new View2D( this );

		View3D* l_3D_view  = new View3D( this );
	
		m_views.push_back( l_axial_view );
		m_views.push_back( l_sagit_view );
		m_views.push_back( l_coro_view );
		m_views.push_back( l_3D_view );

		// setup 2D views
		l_axial_view->setPlaneOrientation( 0 );
		l_sagit_view->setPlaneOrientation( 1 );
		l_coro_view->setPlaneOrientation( 2 );

		// build a simple layout for now

		QHBoxLayout* l_main_layout = new QHBoxLayout;
		this->setLayout( l_main_layout );
		l_main_layout->setContentsMargins( QMargins() );
		l_main_layout->setSpacing( 0 );


		QVBoxLayout* l_left_layout = new QVBoxLayout;
		l_left_layout->setContentsMargins( QMargins() );
		l_left_layout->setSpacing( 0 );

		QHBoxLayout* l_bottom_left_layout = new QHBoxLayout;
		l_bottom_left_layout->setContentsMargins( QMargins() );
		l_bottom_left_layout->setSpacing( 0 );

		l_bottom_left_layout->addWidget( l_coro_view );
		l_bottom_left_layout->addWidget( l_sagit_view );

		l_left_layout->addWidget( l_axial_view, 3 );
		l_left_layout->addLayout( l_bottom_left_layout, 2 );

		l_main_layout->addLayout( l_left_layout, 3 );
		l_main_layout->addWidget( l_3D_view, 2 );

		m_volume = NULL;
	}
	
	Viewer::~Viewer(){
		if( m_volume )
			m_volume->Delete();
	}

	
	void Viewer::setVolume( vtkImageData* a_volume ){
		Q_ASSERT( a_volume );
		m_volume = a_volume;
		for( int i=0; i<m_views.size(); i++ ){
			m_views[i]->setVolume( m_volume );
		}
	}

	vtkImageData* Viewer::getVolume(){
		return m_volume;
	}

	void Viewer::onOpenVolumeButton(){

		QString l_dir = QFileDialog::getExistingDirectory( this, "Open Dicom Directory" );

		if( l_dir.isNull() )
			return;

		if( m_volume )
			m_volume->Delete();
		m_volume = vtkImageData::New();


		vtkDICOMImageReader* l_reader = vtkDICOMImageReader::New();
		l_reader->SetDirectoryName( l_dir.toUtf8().data() );
		l_reader->Update();

		
		m_volume->DeepCopy( l_reader->GetOutput() );
		l_reader->Delete();
		this->setVolume( m_volume );

	}
}



