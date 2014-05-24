#ifndef DEE_LOGGER_H
#define DEE_LOGGER_H

#include "deeCore.h"

namespace dee{
    class LoggerManager : public QObject{

        Q_OBJECT
	
    public:
        LoggerManager();
        virtual ~LoggerManager();
		
	};
	
}

#endif
