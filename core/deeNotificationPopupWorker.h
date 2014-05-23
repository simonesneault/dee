
#ifndef DEE_NOTIFICATION_POPUP_WORKER_H
#define DEE_NOTIFICATION_POPUP_WORKER_H


#include <QObject>

namespace dee{
    /**
     * \class NotificationPopupWorker
     * \brief Worker to be used with NotificationPopup
     *
     * This class will be given to a thread and control the notification UI
     *
     * \author simon.esneault@therenva.com
     * \date 7 2013
     * \see NotificationPopup
     */
    class NotificationPopupWorker : public QObject {

        Q_OBJECT

    public :
        NotificationPopupWorker();
        virtual ~NotificationPopupWorker();

    public slots:
        void start();

    signals:
        void finished();
        void updateOpacity( double );
    };

}
#endif
