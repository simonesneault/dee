#include "deeProfilerElement.h"

#include "deeProfilerManager.h"
#include "deeCore.h"

namespace dee{
	ProfilerElement::ProfilerElement( const QString& a_function_name ): m_func_name( a_function_name ){
		m_timer.start();
		Core::Engine().getProfilerManager()->startProfile( *this );
	}
	
	ProfilerElement::~ProfilerElement(){
		m_value = m_timer.elapsed() / 1000.;
		Core::Engine().getProfilerManager()->endProfile( *this );
	}
}