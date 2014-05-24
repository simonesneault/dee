#include "deeProfilerManager.h"
#include "deeCore.h"


#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>

#ifdef WIN32
	#define RED		12
	#define GREEN	11
	#define YELLOW	10
	#define WHITE	7
#else
	#define RED		"\033[01;31m"
	#define GREEN	"\033[01;32m"
	#define YELLOW	"\033[01;33m"
	#define WHITE	"\033[01;37m"
#endif

namespace dee{

	ProfilerManager::ProfilerManager() : m_indent_level( -1 ), m_is_paused( false ){}

	ProfilerManager::~ProfilerManager(){}

	void ProfilerManager::clear(){
		m_indent_level = -1;
		m_call_count_map.clear();
	}
		
	void ProfilerManager::pauseProfiler( bool a ){
		m_is_paused = a;
	}

	void ProfilerManager::startProfile( ProfilerElement& a_event ){
			
		if( m_is_paused )
			return;
			
		if ( m_call_count_map.find( a_event.m_func_name ) != m_call_count_map.end() )
			m_call_count_map[ a_event.m_func_name ] ++;
		else 
			m_call_count_map[ a_event.m_func_name ] = 1;

		increaseIndent();
			
		QString l_debug_out = getIndentString();
		QString l_func_name = a_event.m_func_name;
		l_func_name.replace( "void ", "");
		l_func_name.replace( "unsigned ", "u" );
		l_func_name.replace( "PixelType = ", "Pix=" );
		l_func_name.replace( "int Dimension = ", "Dim=" );
		l_func_name.replace( "PixelType", "Pix" );
		l_func_name.replace( "Dimension", "Dim" );			
					
		l_debug_out += "START " + l_func_name.left(90)  + " #" + QString().setNum( m_call_count_map[ a_event.m_func_name ] );
			
		// add light red color output if it's linux, and then back to white
		#ifdef LINUX
		l_debug_out = RED + l_debug_out + WHITE;	
		#endif			
			
		#ifdef WIN32
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), RED );
		std::cout << l_debug_out.toStdString() << std::endl;
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), WHITE );
		#else
		std::cout << l_debug_out << << std::endl;
		#endif
	}

	void ProfilerManager::endProfile( ProfilerElement& a_event ) {
			
		if( m_is_paused )
			return;
	
		QString l_debug_out = getIndentString();
		QString l_func_name = a_event.m_func_name;
		l_func_name.replace( "void ", "");
		l_func_name.replace( "unsigned ", "u" );
		l_func_name.replace( "PixelType = ", "Pix=" );
		l_func_name.replace( "int Dimension = ", "Dim=" );
		l_func_name.replace( "PixelType", "Pix" );
		l_func_name.replace( "Dimension", "Dim" );	
			
		l_debug_out += "END   " + l_func_name.left(90) + " #" + QString().setNum( m_call_count_map[ a_event.m_func_name ] );
			
		// add light green color output if it's linux
		#ifdef LINUX
		l_debug_out += YELLOW + QString( " Time: " ) + QString().setNum( a_event.m_value, 'g', 3 )  + " s.";
		l_debug_out = GREEN + l_debug_out + WHITE;
		#endif

		#ifdef OSX
		l_debug_out += " Time: " + QString().setNum( a_event.m_value, 'g', 3 )  + " s.";
		#endif 

		#ifdef WIN32
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), YELLOW );
		std::cout << l_debug_out.toStdString();
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), GREEN );
		std::cout << QString( " Time: " + QString().setNum( a_event.m_value, 'g', 3 ) + " s." ).toStdString() << std::endl;
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), WHITE );
		#else
		std::cout << l_debug_out << std::endl;
		#endif

		decreaseIndent();
	}

	QString ProfilerManager::getIndentString() {
		QString l_indent_string = "";
		for( int i=0; i<m_indent_level; i++ )
			l_indent_string += "|  ";

		return l_indent_string;
	}

}