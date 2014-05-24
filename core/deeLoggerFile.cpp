#include "deeLoggerFile.h"

namespace dee{
  	
	LoggerFile::LoggerFile( const QString& a_filename ) : Logger(){
		m_file.setFileName( a_filename );
		m_file.open( QIODevice::Append | QIODevice::Text );	
	}

	LoggerFile::~LoggerFile(){
		m_file.close();
	}
	
	void LoggerFile::print( const QString& a_message ){

		QString l_message = a_message;
#ifdef LINUX			
		l_message.replace("\033[01;31m", "" );
		l_message.replace("\033[01;32m", "" );
		l_message.replace("\033[01;33m", "" );
		l_message.replace("\033[01;34m", "" );
		l_message.replace("\033[01;35m", "" );			
		l_message.replace("\033[01;37m", "" );
		l_message.replace("\033[00;33m", "" );	
		l_message.replace("\033[00;35m", "" );	
		l_message.replace("\033[00;37m", "" );
#endif
		
		QTextStream l_text_stream( &m_file );
		l_text_stream.setCodec( "UTF-8" );
		l_text_stream << a_message;
	}
}
