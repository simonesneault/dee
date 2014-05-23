#include "deeNotificationManager.h"
#include "deeNotificationPopupWorker.h"

#include "deeNotificationPopup.h"

#include <QApplication>
#include <QThread>
#include <QWidget>

namespace dee{

    void NotificationManager::notify( const QString& a_message, QWidget* a_parent_widget /*=NULL*/, const QString& a_icon_path /*="images/icon-endosize.png"*/ ){


        // create an application locker

        // create a qthread
        QThread *l_thread = new QThread;


        NotificationPopup *l_popup = new NotificationPopup( a_message, a_icon_path, a_parent_widget );
        NotificationPopupWorker *l_worker = new NotificationPopupWorker();
        l_worker->moveToThread( l_thread );

        // connection
        QObject::connect( l_thread, SIGNAL( started() ),  				l_worker, 	SLOT( start() ),				Qt::QueuedConnection );
        QObject::connect( l_worker, SIGNAL( updateOpacity( double ) ), 	l_popup, 	SLOT( setOpacity( double ) ),	Qt::QueuedConnection );
        QObject::connect( l_worker, SIGNAL( finished() ), 				l_thread, 	SLOT( quit() ),					Qt::QueuedConnection );
        QObject::connect( l_worker, SIGNAL( finished() ), 				l_popup, 	SLOT( deleteLater() ),			Qt::QueuedConnection );
        QObject::connect( l_worker, SIGNAL( finished() ), 				l_worker, 	SLOT( deleteLater() ),			Qt::QueuedConnection );
        QObject::connect( l_worker, SIGNAL( destroyed( QObject* ) ), 	l_thread, 	SLOT( deleteLater() ),			Qt::QueuedConnection );

        // start thread
        l_thread->start();
    }


}
