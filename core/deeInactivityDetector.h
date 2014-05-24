#ifndef DEE_INACTIVITY_DETECTOR_H
#define DEE_INACTIVITY_DETECTOR_H

#include "deeCore.h"

namespace dee{

	class InactivityDetector : public QObject {
		
        Q_OBJECT

	public:
		
		InactivityDetector( int a_timeout_seconds = 20, QObject *parent = 0 );
		virtual ~InactivityDetector();
		
        int inactivityTimeOut () const { return m_time_out; }
        void setInactivityTimeOut ( int msec ) { m_time_out = msec; }
		
		bool isInactive(){ return m_is_inactive; }
		
	signals:
		void userInactive();
		void userActive();
		
	public slots:
		void timeout();
		
	protected:
		bool eventFilter( QObject *obj, QEvent *event );
		
	private:
        QTimer *m_timer;
		int m_time_out;
		bool m_is_inactive;
	};

}
#endif
