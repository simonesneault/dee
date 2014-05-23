#ifndef DEE_NOTIFICATION_POPUP_H
#define DEE_NOTIFICATION_POPUP_H

#include <QWidget>

namespace dee{

    /**
     * \class NotificationPopup
     * \brief Notification Popup UI
     *
     * Widget displayed as a popup to mimic a notification
     *
     * \author simon.esneault@gmail.com
     * \date 2013
     * \see NotificationPopupWorker
     */

    class NotificationPopup : public QWidget {

        Q_OBJECT

    public :
        NotificationPopup( QString a_message, QString a_icon_path, QWidget* a_parent );
        virtual ~NotificationPopup();

    public slots:
        void setOpacity( double a );
    };

}
#endif
