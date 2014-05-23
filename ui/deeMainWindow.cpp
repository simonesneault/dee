#include "deeMainWindow.h"

#include "deeViewer.h"

#include <QtWidgets>

namespace dee{
	MainWindow::MainWindow( QWidget* a_parent /*=NULL*/ ){
		QHBoxLayout* l_main_layout = new QHBoxLayout;
		this->setLayout( l_main_layout );
		l_main_layout->setSpacing( 0 );
		l_main_layout->setContentsMargins( QMargins() );

		// Build left panel
		QWidget* l_left_panel = new QWidget;
		l_left_panel->setMinimumWidth( 200 );
		l_left_panel->setMaximumWidth( 200 );
		QVBoxLayout* l_left_layout = new QVBoxLayout;
		l_left_panel->setLayout( l_left_layout );

		QGroupBox* l_group_box_open = new QGroupBox( "Data" );
		l_group_box_open->setLayout( new QVBoxLayout );
		QPushButton* l_open = new QPushButton( "Open" );
		l_group_box_open->layout()->addWidget( l_open );

		l_left_layout->addWidget( l_group_box_open );
		l_left_layout->addStretch();


		m_viewer = new Viewer( this );
		
		connect( l_open, SIGNAL( pressed() ), m_viewer, SLOT( onOpenVolumeButton() ) );

		l_main_layout->addWidget( l_left_panel );
		l_main_layout->addWidget( m_viewer );	

		this->setMinimumSize( 960, 720 );
	}
	
	MainWindow::~MainWindow(){
	
	}

}



