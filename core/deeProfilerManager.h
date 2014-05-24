#ifndef DEE_PROFILER_H
#define DEE_PROFILER_H

#include "deeCore.h"

namespace dee{
		
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

}

#endif