#include "deeOsirixTfReader.h"

#include <QDebug>
#include <QDomDocument>
#include <QFile>

namespace dee{

    OsirixTfReader::OsirixTfReader( const QString& a_plist_path ){

        m_plist_path = a_plist_path;

        m_blue = new uchar[256];
        m_red = new uchar[256];
        m_green = new uchar[256];
    }

    OsirixTfReader::~OsirixTfReader(){
        delete [] m_blue;
        delete [] m_red;
        delete [] m_green;
    }

    bool OsirixTfReader::read(){

        QFile l_file( m_plist_path );

        if( !l_file.open( QIODevice::ReadOnly ) ){
            qWarning() << "Osirix Tf Reader couldn't open the file " << m_plist_path;
            return false;
        }

        QDomDocument l_dom;

        if( !l_dom.setContent( &l_file ) ){
            qWarning() << "Osirix Tf Reader content of file " << m_plist_path << " is invalid ";
            return false;
        }

        l_file.close();

        QDomElement l_root = l_dom.documentElement();
        QDomNodeList l_key_list =  l_root.elementsByTagName( "key" );
        QDomNodeList l_array_list =  l_root.elementsByTagName( "array" );

        if( l_key_list.size() != 3 || l_array_list.size() != 3){
             qWarning() << "File is invalid : " << m_plist_path;
            return false;
        }

        // read blue
        if( l_key_list.item( 0 ).toElement().text() != "Blue" || l_key_list.item( 0 ).lineNumber() != l_array_list.item( 0 ).lineNumber() - 1 ){
              qWarning() << "File is invalid for blue : " << m_plist_path;
            return false;
        }
        QDomNodeList l_blue_list = l_array_list.item( 0 ).childNodes();
        if ( l_blue_list.count() != 256 ){
              qWarning() << "Blue should be defined on 256 color  : " << m_plist_path;
            return false;
        }

        for( int i=0; i< l_blue_list.size() ; i++ ){
            QDomElement l_elem = l_blue_list.item( i ).toElement();
            m_blue[i] = l_elem.text().toInt();
        }

        // read green
        if( l_key_list.item( 1 ).toElement().text() != "Green" ||
            l_key_list.item( 1 ).lineNumber() != l_array_list.item( 1 ).lineNumber() - 1 ){
              qWarning() << "File is invalid for green : " << m_plist_path;
            return false;
        }
        QDomNodeList l_green_list = l_array_list.item( 1 ).childNodes();
        if ( l_green_list.count() != 256 ){
             qWarning() << "Green should be defined on 256 color  : " << m_plist_path;
            return false;
        }
        for( int i=0; i< l_green_list.size() ; i++ ){
            QDomElement l_elem = l_green_list.item( i ).toElement();
            m_green[i] = l_elem.text().toInt();
        }

        // read red
        if( l_key_list.item( 2 ).toElement().text() != "Red" ||
            l_key_list.item( 2 ).lineNumber() != l_array_list.item( 2 ).lineNumber() - 1 ){
              qWarning() << "File is invalid for red : " << m_plist_path;
            return false;
        }
        QDomNodeList l_red_list = l_array_list.item( 2 ).childNodes();
        if ( l_red_list.count() != 256 ){
              qWarning() << "Red should be defined on 256 color  : " << m_plist_path;
            return false;
        }
        for( int i=0; i< l_red_list.size() ; i++ ){
            QDomElement l_elem = l_red_list.item( i ).toElement();
            m_red[i] = l_elem.text().toInt();
        }

        return true;
    }


}
