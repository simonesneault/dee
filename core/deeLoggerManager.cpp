#include "deeLoggerManager.h"

#include "deeLogger.h"


namespace dee{
    LoggerManager::LoggerManager(){

    }

    LoggerManager::~LoggerManager(){
		for( int i=0; i<m_loggers.size(); i++ ){
			delete m_loggers[i];
		}
		m_loggers.clear();
    }

	void LoggerManager::addLogger( Logger* a_logger ){
		m_loggers.push_back( a_logger );
	}

	void LoggerManager::print( const QString& a_message ){

		for( int i=0; i<m_loggers.size(); i++ ){
			m_loggers[i]->print( a_message );
		}
	}
}