
#ifndef DEE_BUSY_WIDGET_H
#define DEE_BUSY_WIDGET_H

#include <QWidget>
#include <QProgressDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QMovie>

#include <QSvgRenderer>
#include <QThread>

namespace dee{

    class Overlay : public QWidget {

        Q_OBJECT

    public:
        Overlay( QSvgRenderer* a_renderer, QWidget* a_parent = NULL );

        void setRotation( double a_rotation ){ m_rotation = a_rotation; }

    protected:
        void paintEvent( QPaintEvent * a_event );

        QSvgRenderer*	m_renderer;
        double			m_rotation;
    };

    class BusyWidget : public QWidget {

        Q_OBJECT

    protected :
        QSvgRenderer*		m_svg_renderer;
        QString             m_label;
        int					m_timer_id;
        double				m_rotation;
        bool				m_is_busy;
        Overlay*			m_overlay_widget;
        QWidget*			m_main_widget;

    public :
        BusyWidget( const QString& a_text = "", QWidget* a_parent = NULL );
        virtual ~BusyWidget();

        virtual void timerEvent( QTimerEvent* a_event );
        virtual void resizeEvent( QResizeEvent* a_event );
        void setMainLayout( QLayout* a_layout );

        void setText( const QString& );

        bool isBusy() { return m_is_busy; }
    public slots :
        void setBusy( bool a_busy = true );
    };

    class BusyDialog : public QDialog {
    protected :
        BusyWidget*	m_busy_widget;
    public :
        BusyDialog( const QString& a_text = "", QWidget* a_parent = NULL );
        virtual ~BusyDialog();

        void setText( const QString& );
    };

}
#endif
