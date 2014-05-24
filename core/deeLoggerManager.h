#ifndef DEE_LOGGER_MANAGER_H
#define DEE_LOGGER_MANAGER_H

#include "deeCore.h"

namespace dee{
	class Logger;
    class LoggerManager : public QObject{

        Q_OBJECT
	
		QVector<Logger*> m_loggers;

    public:
        LoggerManager();
        virtual ~LoggerManager();

		void addLogger( Logger* );
		void print( const QString& );
		
	};
	
}

#endif
