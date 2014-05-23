#include "deeBusyWidget.h"

#include <QTimerEvent>
#include <QPainter>
#include <QCoreApplication>
#include <QPaintEvent>
#include <QGraphicsEffect>


namespace dee{
    #define SVG_SIZE 80
    #define SVG_SIZE_HALF SVG_SIZE/2


    Overlay::Overlay( QSvgRenderer* a_renderer, QWidget *a_parent /*= NULL*/ ):
        QWidget( a_parent ),
        m_renderer( a_renderer ),
        m_rotation( 0 )
    {
        this->setPalette( Qt::transparent );
        this->setAttribute( Qt::WA_TransparentForMouseEvents );

    }

    void Overlay::paintEvent( QPaintEvent * a_event ) {

        int intRotation = int(m_rotation);

        double l_middle_x = (double)width() / 2.0;
        double l_middle_y = (double)height() / 2.0;

        QPointF l_middle( l_middle_x, l_middle_y );
        QRectF l_rect_svg( QPointF( l_middle_x - SVG_SIZE_HALF, l_middle_y - SVG_SIZE_HALF ), QSize( SVG_SIZE, SVG_SIZE ) );

        QRectF l_rect_text( QPointF( 0, l_middle_y - SVG_SIZE_HALF*1.5 ), QSize( width(), 10 ) );

        QPainter l_painter( this );
        l_painter.setOpacity(l_painter.opacity() / 2);

        l_painter.save();
        l_painter.translate( l_middle );
        l_painter.rotate( intRotation );
        l_painter.translate( -l_middle );
        m_renderer->render( &l_painter, l_rect_svg );
        l_painter.restore();

    }


    BusyWidget::BusyWidget(const QString& a_text /*= ""*/, QWidget *a_parent /*= NULL*/)
        : QWidget ( a_parent ),
          m_label( a_text ),
          m_timer_id( 0 ),
          m_rotation( 0 ),
          m_is_busy( false )
    {
        m_svg_renderer = new QSvgRenderer;
        m_svg_renderer->load( QString( "Data/waitsvg.svg" ) );

        this->setContentsMargins( QMargins() );
        m_main_widget = new QWidget( this );

        m_overlay_widget = new Overlay( m_svg_renderer, this );
        m_overlay_widget->hide();
    }

    BusyWidget::~BusyWidget() {
        delete m_svg_renderer;
    }

    void BusyWidget::setText( const QString& a_text ){
         m_label = a_text;
    }

    void BusyWidget::setMainLayout( QLayout *a_layout ){
        m_main_widget->setLayout( a_layout );
    }

    void BusyWidget::setBusy( bool a_busy ) {
        if( m_is_busy == a_busy ) return;

        m_is_busy = a_busy;

        if( m_is_busy == true ) {

            m_timer_id = startTimer( 150 );
            this->setEnabled( false );
            m_overlay_widget->show();
        }
        else {
            killTimer( m_timer_id );
            this->setEnabled( true );
            m_timer_id = 0;
            m_overlay_widget->hide();
        }
    }

    void BusyWidget::timerEvent(QTimerEvent *a_event) {
        if( a_event->timerId() != m_timer_id ) {
            QObject::timerEvent( a_event );
            return;
        }

        m_rotation += 36;
        double l_overflow = m_rotation - 360;
        if ( l_overflow > 0) {
            m_rotation = l_overflow;
        }

        m_overlay_widget->setRotation( m_rotation );
        m_overlay_widget->update();
    }

    void BusyWidget::resizeEvent( QResizeEvent* a_event ){
        m_main_widget->resize( a_event->size() );
        m_overlay_widget->resize( a_event->size() );
        a_event->accept();
    }

    BusyDialog::BusyDialog( const QString& a_text /*=""*/, QWidget* a_parent /*=NULL*/ )
        : QDialog( a_parent ) {

        QFont l_font = this->font();
        l_font.setPointSize( 12 );
        this->setFont( l_font );

        QVBoxLayout* l_main_layout = new QVBoxLayout;
            QLabel* l_label = new QLabel( a_text );
            l_label->setAlignment( Qt::AlignCenter );
            l_main_layout->addWidget( l_label, 1 );

            m_busy_widget = new BusyWidget( a_text );
            m_busy_widget->setBusy();

            l_main_layout->addWidget( m_busy_widget, 2 );

        this->setStyleSheet( "color : #ffffff;" );
        this->setLayout( l_main_layout );
        this->setFixedSize( QSize( 250, 150 ) );

    }

    BusyDialog::~BusyDialog() {}

    void BusyDialog::setText( const QString& a_text ) {
        m_busy_widget->setText( a_text );
    }

}
