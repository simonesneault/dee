#ifndef DEE_LOGGER_FILE_H
#define DEE_LOGGER_FILE_H

#include "deeLogger.h"

namespace dee{

	class LoggerFile : public Logger{
	
		Q_OBJECT
		
	protected:
		QFile m_file;
	
	public:
		LoggerFile( const QString& a_file_name );
        virtual ~LoggerFile();
	
		virtual void print( const QString &a_message );
		
    };
}

#endif
