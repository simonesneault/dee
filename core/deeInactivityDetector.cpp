#include "deeInactivityDetector.h"

#include <QtGui>
#include <QtCore>

namespace dee{
	
	InactivityDetector::InactivityDetector( int a_timeout_seconds /*= 20*/, QObject *parent /*=NULL*/ ) 
		: QObject(parent), m_time_out( a_timeout_seconds * 1000 ), m_is_inactive( false )
	{

        m_timer = new QTimer( this );
        m_timer->start( m_time_out );
        connect( m_timer, SIGNAL( timeout() ), this, SLOT( timeout() ) );

        qApp->installEventFilter( this );

	}
	
	InactivityDetector::~InactivityDetector(){
        disconnect( m_timer, SIGNAL( timeout() ), this, SLOT( timeout() ) );
        qApp->removeEventFilter( this );

        if( m_timer != NULL ){
            delete m_timer;
		}
		
		
	}
	
    bool InactivityDetector::eventFilter( QObject *obj, QEvent *event )
	{
		// this is needed or else the timer is reset by its own timeout signal event before the signal is sent
        if( event->type() != QEvent::Timer ) {
            m_timer->start( m_time_out );
			//Emit user activity only once
			if( m_is_inactive == true ) {
				emit userActive();
			}
			m_is_inactive = false;
		}
		return QObject::eventFilter( obj, event ); // just a wrapper, we don't want to override any events
	}
	
	void InactivityDetector::timeout(){

        //NOTE only emit userInactive if the app has the focus
        if( qApp->focusWindow() != NULL ){
            m_is_inactive = true;

            emit userInactive();
        }

	}
}
