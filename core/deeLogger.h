#ifndef DEE_LOGGER_H
#define DEE_LOGGER_H

#include "deeCore.h"

namespace dee{
    class Logger : public QObject{

        Q_OBJECT
	
    public:
        Logger();
        virtual ~Logger();
		
		virtual void print( const QString &a_message );
	
		const Logger& operator<<( const QString& );
	};
	
}

#endif
