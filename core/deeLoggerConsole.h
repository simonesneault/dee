#ifndef DEE_LOGGER_CONSOLE_H
#define DEE_LOGGER_CONSOLE_H

#include "deeLogger.h"

namespace dee{
    class LoggerConsole : public Logger, public QScrollArea{
			
		Q_OBJECT

	protected:
		QLabel*		m_log_view;
		QString 	m_log_buffer;
			
	public:
		
		LoggerConsole( QWidget* a_parent );
		virtual ~LoggerConsole();
			
		virtual void print( const QString &a_message );
		
			
	};
}

#endif
