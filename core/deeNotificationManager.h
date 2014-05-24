
#ifndef DEE_NOTIFICATION_MANAGER_H
#define DEE_NOTIFICATION_MANAGER_H

#include "deeCore.h"

namespace dee{

	/**
	 * \class NotificationManager
	 * \brief Manage Notification
	 * 
	 * 
	 * \author simon.esneault@gmail.com
	 * \date 7 2013
	 * \see NotificationPopup
	*/
	
    class NotificationManager : public QObject{
		
        Q_OBJECT

	public:
		static void notify( const QString& a_message, QWidget* a_parent_widget=NULL, const QString& a_icon_path="images/icon-endosize.png" );

		
	};
}
#endif
