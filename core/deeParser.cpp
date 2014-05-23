#include "deeParser.h"

namespace dee{
    Parser::Parser(){
        m_file_size_min = -1;
        m_file_size_max = -1;
        m_file_hidden = false;
    }
    Parser::~Parser(){

    }


    void Parser::setInputDir( const QString& a_dir ){
        m_input_dir = a_dir;
    }

    void Parser::setFileExtensions( const QStringList& a_ext ){
        m_file_extension = a_ext;
    }

    void Parser::setFileSizeRange( double, double ){

    }

    void Parser::setFileModificationRange( QDate, QDate ){

    }

    void Parser::setFileCreationRange( QDate, QDate ){

    }

    void Parser::parseFileHidden( bool a_hidden ){
        m_file_hidden = a_hidden;
    }

    QFileInfoList Parser::getOutputFiles(){

        //TODO sort output
        // use QDirIterator only for directories
        // then use
        // QDir::entryInfoList( m_file_extension,
        //      QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot,
        //      QDir::Name );
        QFileInfoList l_out;
        QDir l_in( m_input_dir );
        QDirIterator l_it( l_in.absolutePath(), QDirIterator::Subdirectories );
        while( l_it.hasNext() ){
            l_it.next();
            QFileInfo l_file = l_it.fileInfo();
            if( !l_file.isDir() ){
                if( !( m_file_hidden && l_file.isHidden() ) ){
                    if( !m_file_extension.isEmpty() && m_file_extension.contains( l_file.suffix() ) ){
                        l_out.push_back( l_file );
                    }
                }
            }
        }
        return l_out;

    }
}
