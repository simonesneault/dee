#include "deeCore.h"

// manager
#include "deeLoggerManager.h"
#include "deeNotificationManager.h"
#include "deeProfilerManager.h"

// loggers
#include "deeLogger.h"
#include "deeLoggerFile.h"
		
namespace dee{
	Core Core::m_instance=Core();

	// constructor
	Core::Core(){
		m_application = NULL;
		m_logger_manager = NULL;
		m_notification_manager = NULL;
		m_profiler_manager = NULL;
	}

	// destructor
	Core::~Core(){
		if( m_logger_manager )
			delete m_logger_manager;
		if( m_notification_manager )
			delete m_notification_manager;
		if( m_profiler_manager )
			delete m_profiler_manager;
	}

	Core& Core::Engine(){
		return m_instance;
	}
	
	bool Core::Start( QApplication* a_application ){

		QString l_date = QDate::currentDate().toString( "yyyy-MM-dd" );
		QString l_time = QDate::currentDate().toString( "yyyy-MM-dd" );

		m_application = a_application;

		// start logger
		m_logger_manager = new LoggerManager();

		m_logger_manager->addLogger( new Logger() );
		m_logger_manager->addLogger( new LoggerFile( QDir::tempPath() + "dee-"+ l_date + "-" + l_time + ".log" ) );

		
		m_notification_manager = new NotificationManager();
		m_profiler_manager = new ProfilerManager();

		// notice !
		M_Notice( "dee3 started : " + l_date + " - " + l_time );
		return true;
	}

	QApplication* Core::getApplication(){
		return m_application;
	}

	LoggerManager* Core::getLoggerManager(){
		return m_logger_manager;
	}

	ProfilerManager* Core::getProfilerManager(){
		return m_profiler_manager;
	}

	NotificationManager* Core::getNotificationManager(){
		return m_notification_manager;
	}

	void Core::notify( const char* a_file, const char* a_func, int a_line, int a_priority, const QString& a_message ){

		QString l_message;
		
		if( ( a_message == "" ) || ( a_message == " " ) ){
			l_message = "";
		}
		else{
			
			switch( a_priority ){
				case 0:
					l_message="Notice:   ";
					break;
				case 1:
					l_message="Warning:  ";
					break;
				case 2:
					l_message="Error:    ";
					break;
			
				default:
					break;
			}
			
			QString l_file( a_file);
			
					
			l_file.replace( "\\", "/" );
			
			l_file = l_file.right( l_file.lastIndexOf( "/" ) );

			l_file.replace( "_", "::" );
			l_file.replace( ".cpp", "" );
			l_file.replace( ".h", "" );

			l_file += "::";

			QString l_func( a_func );
			l_func.replace( "virtual ", "" );
			
	
			if( a_priority==0 )
				l_file = l_func;
			else
				l_file += l_func;
			
#ifdef LINUX
			if( a_priority==TH_PRIORITY_NOTICE ){
				l_message = "\033[00;37m" + l_message + "\033[01;37m";					
				l_file = "\033[00;37m" + l_file + "\033[01;37m";	
			}
			else{
				l_message = "\033[00;35m" + l_message + "\033[01;35m";					
				l_file = "\033[00;35m" + l_file + "\033[01;37m";	
			}	
#endif

			QString l_indent;
			
			l_message =  l_message + l_indent + "  " + a_message + " || " + l_file  + ":"+ QString().setNum( a_line );

			m_logger_manager->print( l_message );
		}

	}



}