
#ifndef DEE_OVERLAY_PAINTING_WIDGET_H
#define DEE_OVERLAY_PAINTING_WIDGET_H

#include <QWidget>

namespace dee{

    class OverlayPaintingWidget : public QWidget {

        Q_OBJECT

    private:

        bool 			m_scribbling;
        int 			m_pen_width;
        QColor 			m_pen_color;
        QImage 			m_image;
        QPoint 			m_last_point;
        QVector<QPoint> m_points;

    public:
        OverlayPaintingWidget( QWidget* a_parent = 0 );

        void setBackImage( const QImage& );
        void setPenColor( const QColor& );
        void setPenWidth( int );

        QVector<QPoint> getPoints(){ return m_points; };

        void clear();

    signals:
        void mouseReleased();
    protected:
        void mousePressEvent( QMouseEvent* );
        void mouseMoveEvent( QMouseEvent* );
        void mouseReleaseEvent( QMouseEvent* );
        void paintEvent( QPaintEvent* );
        void resizeEvent( QResizeEvent* );

    private :
        void drawLineTo( const QPoint& );


    };
}
#endif
