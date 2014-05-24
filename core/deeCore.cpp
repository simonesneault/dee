#include "deeCore.h"

#include "deeNotificationManager.h"
#include "deeProfilerManager.h"

#include <QtCore>

namespace dee{
	
	Core Core::m_instance=Core();

	// constructor
	Core::Core(){
		m_application = NULL;
		m_notification_manager = NULL;
		m_profiler_manager = NULL;
	}

	// destructor
	Core::~Core(){
		if( m_notification_manager )
			delete m_notification_manager;
		if( m_profiler_manager )
			delete m_profiler_manager;
	}

	Core& Core::Engine(){
		return m_instance;
	}
	
	bool Core::Start( QApplication* a_application ){
		m_application = a_application;
		m_notification_manager = new NotificationManager();
		m_profiler_manager = new ProfilerManager();
		return true;
	}

	QApplication* Core::getApplication(){
		return m_application;
	}

	ProfilerManager* Core::getProfilerManager(){
		return m_profiler_manager;
	}

	NotificationManager* Core::getNotificationManager(){
		return m_notification_manager;
	}



}