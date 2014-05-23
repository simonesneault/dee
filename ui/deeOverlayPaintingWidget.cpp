#include "deeOverlayPaintingWidget.h"

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>

namespace dee{
		
    OverlayPaintingWidget::OverlayPaintingWidget( QWidget* a_parent /*=0*/ ):
        QWidget( a_parent )
    {
        this->setWindowFlags( Qt::FramelessWindowHint );
        this->setAttribute( Qt::WA_StaticContents );
        m_scribbling = false;
        m_pen_width = 2;
        m_pen_color = Qt::green;
    }

    void OverlayPaintingWidget::setPenColor( const QColor& a_new_color ){
        m_pen_color = a_new_color;
    }

    void OverlayPaintingWidget::setPenWidth( int a_new_width ){
        m_pen_width = a_new_width;
    }

    void OverlayPaintingWidget::setBackImage( const QImage& a_image ){
        m_image = a_image;
        this->update();
    }

    void OverlayPaintingWidget::clear(){
        m_points.clear();
        m_scribbling = false;
        m_pen_width = 2;
        m_pen_color = Qt::green;
    }

    void OverlayPaintingWidget::mousePressEvent( QMouseEvent *a_event ){
        if ( a_event->button() == Qt::LeftButton ) {
            m_last_point = a_event->pos();
            m_points.push_back( m_last_point );
            m_scribbling = true;
        }
    }

    void OverlayPaintingWidget::mouseMoveEvent( QMouseEvent *a_event ){
        if ( ( a_event->buttons() & Qt::LeftButton ) && m_scribbling )
            drawLineTo( a_event->pos() );
    }

    void OverlayPaintingWidget::mouseReleaseEvent( QMouseEvent *a_event ){
        if ( a_event->button() == Qt::LeftButton && m_scribbling ) {
            drawLineTo( a_event->pos() );
            m_scribbling = false;
            emit mouseReleased();
        }
    }

    void OverlayPaintingWidget::paintEvent( QPaintEvent *a_event ){
        QPainter l_painter( this );
        QRect l_dirty_rect = a_event->rect();
        l_painter.drawImage( l_dirty_rect, m_image, l_dirty_rect );
    }

    void OverlayPaintingWidget::resizeEvent( QResizeEvent *a_event ){

        if ( this->width() > m_image.width() || this->height() > m_image.height() ) {

            QSize l_new_size( qMax( width() + 128, m_image.width() ), qMax( height() + 128, m_image.height() ) );
            QImage l_new_image( l_new_size, QImage::Format_RGB32 );
            l_new_image.fill( qRgb( 255, 255, 255 ) );
            QPainter l_painter( &l_new_image );
            l_painter.drawImage( QPoint( 0, 0 ), m_image );
            m_image = l_new_image;
            this->update();
        }
        QWidget::resizeEvent( a_event );
    }

    void OverlayPaintingWidget::drawLineTo( const QPoint &a_end_point ){

        m_points.push_back( a_end_point );
        QPainter l_painter( &m_image );
        l_painter.setPen( QPen( m_pen_color, m_pen_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
        l_painter.drawLine( m_last_point, a_end_point );


        int l_rad = ( m_pen_width / 2 ) + 2;
        this->update( QRect( m_last_point, a_end_point ).normalized().adjusted( -l_rad, -l_rad, +l_rad, +l_rad ) );
        m_last_point = a_end_point;
    }

}
