#ifndef DEE_CORE_H
#define DEE_CORE_H

namespace dee{

	class NotificationManager;
	class ProfilerManager;

	/**
	 * Main singleton class, get access from anywhere to all managers
	 */ 
	class Core{
	
	protected:
		NotificationManager*	m_notification_manager;
		ProfilerManager*		m_profiler_manager;
	
	public:
		static Core& Engine();
		
		ProfilerManager* getProfilerManager();
		NotificationManager* getNotificationManager();
		
	private:
		Core& operator= (const Core&){}
		Core (const Core&){}

		static Core m_instance;
		Core();
		~Core();
	};
}

#endif