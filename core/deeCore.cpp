#include "deeCore.h"

#include "deeNotificationManager.h"
#include "deeProfilerManager.h"

namespace dee{
	
	Core Core::m_instance=Core();

	Core::Core(){
		m_notification_manager = new NotificationManager();
		m_profiler_manager = new ProfilerManager();
	}

	Core::~Core(){
		delete m_notification_manager;
		delete m_profiler_manager;
	}

	Core& Core::Engine(){
		return m_instance;
	}

	ProfilerManager* Core::getProfilerManager(){
		return m_profiler_manager;
	}

	NotificationManager* Core::getNotificationManager(){
		return m_notification_manager;
	}


}