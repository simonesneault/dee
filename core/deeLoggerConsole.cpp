#include "deeLoggerConsole.h"

namespace dee{
    LoggerConsole::LoggerConsole( QWidget* a_parent ) : QScrollArea( a_parent ){
		
		m_log_view = new QLabel;

		this->setWidget( m_log_view );
		this->setBackgroundRole( QPalette::BrightText );
		this->setWidgetResizable( true );
	}
    LoggerConsole::~LoggerConsole(){}
	
	
	void LoggerConsole::print( const QString &a_message ){
				
		QString l_line = a_message;
#ifdef LINUX			
		l_line.replace("\033[01;31m", "" );
		l_line.replace("\033[01;32m", "" );
		l_line.replace("\033[01;33m", "" );
		l_line.replace("\033[01;35m", "" );			
		l_line.replace("\033[01;37m", "" );
		l_line.replace("\033[00;35m", "" );			
		l_line.replace("\033[00;37m", "" );
#endif
		if( m_log_buffer == "" )
			l_line.replace( "\n", "<br>" );
		else
			l_line.replace( "\n", "</font><br>" );
		l_line.replace( " ", "&nbsp;" );
		l_line.replace( "||", "<font color=\"grey\">||" ); 
		l_line.replace( "Notice:", "<b>Notice:</b>" );
		l_line.replace( "Warning:", "<font color=\"orange\"><b>Warning:</b></font>" );
		l_line.replace( "Error:", "<font color=\"red\"><b>Error:</b></font>" );

		m_log_buffer+= l_line;
		m_log_view->setText( m_log_buffer );
		m_log_view->update();
		this->update();
		M_RefreshGUI
		
	}
}
