#ifndef DEE_PROFILER_ELEMENT_H
#define DEE_PROFILER_ELEMENT_H

#include <QtCore>

namespace dee{
	class ProfilerElement {
	
	public :			
		QString		m_func_name;
		double		m_value;			
		QTime		m_timer;
		
	public :
		ProfilerElement( const QString& a_function_name );
		virtual ~ProfilerElement();
	};
}

#endif