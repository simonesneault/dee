#ifndef DEE_CORE_H
#define DEE_CORE_H

// Qt includes
#include <QtCore>
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>
#include <QVTKWidget.h>

// VTK classic forward declaration
class vtkImageData;
class vtkGPUVolumeRaycastMapper;
class vtkResliceImageViewer;

// STL includes
#ifdef WIN32
#include <Windows.h>
#endif
#include <iostream>

namespace dee{

	class NotificationManager;
	class ProfilerManager;

	/**
	 * Dee Engine class, handle all managers, intialize everything
	 */ 
	class Core : public QObject{
	
		Q_OBJECT

	protected:
		QApplication*           m_application;
		NotificationManager*	m_notification_manager;
		ProfilerManager*		m_profiler_manager;
	
	public:
		static Core& Engine();

		bool Start( QApplication* a_app );
		
		QApplication* getApplication();
		ProfilerManager* getProfilerManager();
		NotificationManager* getNotificationManager();
		
	private:
		Core& operator= (const Core&){}
		Core (const Core&){}

		static Core m_instance;
		Core();
		~Core();
	};


	// Macro !

	// get Main Engine
	#define M_Engine Dee::Engine()

	// get Directory
	#define M_AppDir Dee::Engine()->getApplication()->applicationDirPath()
	#define M_LogDir M_AppDir + "log/"

	// refresh UI
	#define M_RefreshGUI          qApp->processEvents();
	#define M_RefreshGUIOnly      qApp->processEvents( QEventLoop::ExcludeUserInputEvents );

	// log
	#define M_Throw( level, message ) { stl::Exception l_tmp_exception(__FILE__, M_FunctionName, __LINE__, level, M_Runtime.getIndent(), message); M_Runtime.process( &l_tmp_exception ) ;};
	#define M_LogNum( variable ){ QString message( QString( #variable ) + " : " + QString().setNum( variable ) ); M_Notice( message ); };
	#define M_LogVar( variable ){ QString message( QString( #variable ) + " : " + QString( variable ) ); M_Notice( message ); };
		
	#define M_Notice( message ) { M_Throw( stl::TH_PRIORITY_NOTICE, message ); };
	#define M_Warning( message ) { M_Throw( stl::TH_PRIORITY_WARNING, message ); };
	#define M_Error( message ) { M_Throw( stl::TH_PRIORITY_ERROR, message ); };

}

#endif