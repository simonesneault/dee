#ifndef DEE_OSIRIX_TF_READER_H
#define DEE_OSIRIX_TF_READER_H

#include "deeCore.h"

namespace dee{

    class OsirixTfReader : public QObject{

        Q_OBJECT

    protected:
        QString m_plist_path;
        uchar* m_blue;
        uchar* m_green;
        uchar* m_red;

    public:
        OsirixTfReader( const QString& a_plist_path );
        virtual ~OsirixTfReader();

        bool read();

        uchar* getBlue(){ return m_blue; }
        uchar* getGreen(){ return m_green; }
        uchar* getRed(){ return m_red; }

    };

}

#endif //_DEE_OSIRIX_TF_READER_
