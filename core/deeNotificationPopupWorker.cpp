
#include "deeNotificationPopupWorker.h"
#include "deeNotificationPopup.h"

#include <QApplication>
#include <QTimer>
#include <QThread>

namespace dee{

    NotificationPopupWorker::NotificationPopupWorker(){}

    NotificationPopupWorker::~NotificationPopupWorker(){}

    void NotificationPopupWorker::start(){
        //! smooth animation
        double l_opa_max = 0.8;

        double l_length = 500; // in ms for each step (fade iu, wait, fade out );
        double l_fps = 20;

        double l_time_to_wait = 1000 / l_fps;

        int l_step = static_cast<int>( l_length / l_fps );

        for( int i=0; i<l_step; i++ ){
            double l_opa = ( static_cast<double>( i ) / static_cast<double>( l_step ) ) * l_opa_max;
            emit( updateOpacity( l_opa ) );
            qApp->processEvents();
            QThread::currentThread()->wait( l_time_to_wait );
        }

        QThread::currentThread()->wait( l_length*2 );

        for( int i=0; i<l_step; i++ ){
            double l_opa = ( 1.0 - static_cast<double>( i ) / static_cast<double>( l_step ) ) * l_opa_max;
            emit( updateOpacity( l_opa ) );
            qApp->processEvents();
            QThread::currentThread()->wait( l_time_to_wait );
        }
        qApp->processEvents();
        emit( finished() );
        qApp->processEvents();

	}
}
