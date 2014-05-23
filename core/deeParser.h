#ifndef DEE_PARSER_H
#define DEE_PARSER_H

#include <QtCore>

namespace dee{
    class Parser : public QObject{

        Q_OBJECT


    public:
        Parser();
        virtual ~Parser();

        void setInputDir( const QString& );
        void setFileExtensions( const QStringList& );
        void setFileSizeRange( double, double );
        void setFileModificationRange( QDate, QDate );
        void setFileCreationRange( QDate, QDate );
        void parseFileHidden( bool );

        QFileInfoList getOutputFiles();


    protected:

        QString m_input_dir;
        QStringList m_file_extension;
        double m_file_size_min;
        double m_file_size_max;
        QDate m_file_modif_min;
        QDate m_file_modif_max;
        QDate m_file_creation_min;
        QDate m_file_creation_max;
        bool m_file_hidden;


    };
}

#endif
