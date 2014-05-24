#include "deeLogger.h"



namespace dee{
    Logger::Logger(){
    }
    Logger::~Logger(){}
	
	void Logger::print( const QString &a_message ){
#ifdef WIN32
		if( a_message.contains( "Notice:   " ) ){
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 3 );
		}
		else if( a_message.contains( "Warning:  " ) ){
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 14 );
		}
		else if( a_message.contains( "Error:    " ) ){
			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
		}
		
		
		char *l_buffer = new char[ a_message.size() + 1 ];
		CharToOemA( a_message.toUtf8().data(), l_buffer );
		
		std::cout << l_buffer << std::endl;
		delete [] l_buffer;
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
#else
		std::cout << a_message..toUtf8().data() << std::endl;
#endif
	}	
	
	const Logger& Logger::operator<<( const QString &a_message ){
		this->print( a_message );
		return (*this);
	}
}
