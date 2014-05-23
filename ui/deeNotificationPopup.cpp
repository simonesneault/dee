#include "deeNotificationPopup.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDebug>
#include <QDesktopWidget>
#include <QFrame>
#include <QLabel>

namespace dee{

    NotificationPopup::NotificationPopup( QString a_message, QString a_icon_path /*=""*/, QWidget* a_parent ){


        // transparent background
        this->setAttribute( Qt::WA_TranslucentBackground, true );
        this->setWindowFlags( Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SubWindow );

        //! text in white
        this->setStyleSheet( "#NotificationFrame { background-color: black; border-radius: 12px; border: 2px solid lightGray;}\n"
            "QLabel{ color : white; }" );

        // setup background color :
        QPalette l_palette( this->palette() );
        l_palette.setColor( QPalette::Background,  Qt::black );
        this->setPalette( l_palette );


        //setup things
        QHBoxLayout *l_main_layout = new QHBoxLayout;
        this->setLayout( l_main_layout );
        this->setContentsMargins( QMargins() );

        QFrame *l_frame = new QFrame;
        l_frame->setObjectName( "NotificationFrame" );
        l_frame->setContentsMargins( QMargins() );

        l_main_layout->addWidget( l_frame );


        //setup things
        QHBoxLayout *l_inner_layout = new QHBoxLayout;
        l_frame->setLayout( l_inner_layout );

        if( a_icon_path != "" ){
            QPixmap l_pixmap( a_icon_path );
            QLabel *l_image_label = new QLabel;
            l_image_label->setAlignment( Qt::AlignCenter );
            l_image_label->setPixmap( l_pixmap.scaledToWidth( 48, Qt::SmoothTransformation ) );
            l_inner_layout->addWidget( l_image_label, 1 );
        }

        QLabel *l_label = new QLabel( this );
        l_label->setText( a_message );
        l_label->setAlignment( Qt::AlignCenter );

        QFont l_font = l_label->font();
        l_font.setPointSize( 12 );

        l_label->setFont( l_font );
        l_inner_layout->addWidget( l_label, 2 );

        // setup position
        int l_width = 250;
        int l_height = 100;
        int l_margin = 30;

        QWidget* l_widget = a_parent;
        if( !l_widget )
            l_widget = QApplication::activeWindow();

        QRect l_size;
        if( l_widget )
            l_size = QApplication::desktop()->screenGeometry( l_widget );
        else
            l_size = QApplication::desktop()->screenGeometry();
        this->move( l_size.right() - l_width - l_margin, l_margin );
        this->resize( l_width, l_height );
        this->setWindowOpacity( 0.0 );
        this->show();
        qApp->processEvents();
    }


    NotificationPopup::~NotificationPopup() {
        qDebug() << "Notification | Destroy done ";
    }

    void NotificationPopup::setOpacity( double a ){
        this->setWindowOpacity( a );
    }
}
