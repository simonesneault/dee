#ifndef DEE_PROFILER_H
#define DEE_PROFILER_H

#include "deeCore.h"

namespace dee{

	class ProfilerElement {
		friend class ProfilerManager;

	protected :			
		QString		m_func_name;
		double		m_value;
			
		QTime		m_timer;
	public :
		ProfilerElement( QString a_function_name );
		virtual ~ProfilerElement();
	};

		
	class ProfilerManager: public QObject{

		Q_OBJECT

	protected :
		int 					m_indent_level;
		QMap<QString, double>	m_call_count_map;
		bool 					m_is_paused;

	public :
		ProfilerManager();
		virtual ~ProfilerManager();

		void clear();

		void pauseProfiler( bool );
			
		void startProfile( ProfilerElement& a_event );
		void endProfile( ProfilerElement& a_event );

		void dumpCallCounts();

	protected :
		void increaseIndent() { m_indent_level++; }
		void decreaseIndent() { m_indent_level--; if ( m_indent_level <-1 ) m_indent_level = -1;}
			
		QString getIndentString();
	};

	#ifdef _WIN32
		#define M_StartProfile ProfilerElement l_profile_event( __FUNCTION__ );
	#else 
		#define M_StartProfile ProfilerElement l_profile_event( __PRETTY_FUNCTION__ );
	#endif //_WIN32

	#define M_StartInnerStep( a_step_name ) ProfilerElement* l_profiler_##a_step_name = new ProfilerElement( QString( "InnerStep :    " ) + #a_step_name );

	#define M_EndInnerStep( a_step_name ) delete l_profiler_##a_step_name;

}

#endif