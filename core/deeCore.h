#ifndef DEE_CORE_H
#define DEE_CORE_H

// Qt includes
#include <QtCore>
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>
#include <QVTKWidget.h>

// VTK includes
#include "vtkImageData.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkResliceImageViewer.h"
#include "vtkVolumeProperty.h"

// STL includes
#ifdef WIN32
#include <Windows.h>
#endif
#include <iostream>

// dee includes
#include "deeProfilerElement.h"

namespace dee{

	class LoggerManager;
	class NotificationManager;
	class ProfilerManager;

	/**
	 * Dee Engine class, handle all managers, intialize everything
	 */ 
	class Core : public QObject{
	
		Q_OBJECT

	protected:
		QApplication*           m_application;
		LoggerManager*			m_logger_manager;
		NotificationManager*	m_notification_manager;
		ProfilerManager*		m_profiler_manager;
	
	public:
		static Core& Engine();

		bool Start( QApplication* a_app );
		
		QApplication* getApplication();
		LoggerManager* getLoggerManager();
		ProfilerManager* getProfilerManager();
		NotificationManager* getNotificationManager();

		void notify( const char* a_file, const char* a_func, int a_line, int a_priority, const QString& a_message );
		
	private:
		Core& operator= (const Core&){}
		Core (const Core&){}

		static Core m_instance;
		Core();
		~Core();
	};

	
	// Macro !
	
	// get Main Engine
	#define M_Engine Core::Engine()

	// get Directory
	#define M_AppDir M_Engine.getApplication()->applicationDirPath()
	#define M_LogDir M_AppDir + "log/"

	// refresh UI
	#define M_RefreshGUI          qApp->processEvents();
	#define M_RefreshGUIOnly      qApp->processEvents( QEventLoop::ExcludeUserInputEvents );

	// log
	#ifdef WIN32
		#define M_FunctionName __FUNCTION__
	#else
		#define M_FunctionName __PRETTY_FUNCTION__
	#endif
	#define M_Throw( message, level ) { M_Engine.notify( __FILE__, M_FunctionName, __LINE__, level, message );};
		
	#define M_Notice( message ) { M_Throw( message, 0 ); };
	#define M_Warning( message ) { M_Throw( message, 1 ); };
	#define M_Error( message ) { M_Throw( message, 2 ); };
	
	#define M_LogVar( variable ){ QString message( QString( #variable ) + " : " + QVariant( variable ).toString() ); M_Notice( message ); };


	// profiler
	#ifdef _WIN32
		#define M_StartProfile ProfilerElement l_profile_event( __FUNCTION__ );
	#else 
		#define M_StartProfile ProfilerElement l_profile_event( __PRETTY_FUNCTION__ );
	#endif //_WIN32

	#define M_StartInnerStep( a_step_name ) ProfilerElement* l_profiler_##a_step_name = new ProfilerElement( QString( "InnerStep :    " ) + #a_step_name );

	#define M_EndInnerStep( a_step_name ) delete l_profiler_##a_step_name;
}

#endif