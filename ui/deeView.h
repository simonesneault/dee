#ifndef DEE_VIEW_H
#define DEE_VIEW_H

#include <QVTKWidget.h>

namespace dee{

	/**
	 * @brief Base class for all view in dee3
	 * @author simon.esneault@gmail.com
	 */
	class View : public QVTKWidget{

		Q_OBJECT
		
	protected:
		QString			m_string_id;
		vtkImageData*	m_volume;
		bool			m_is_init;

	public:
		View( QWidget* a_parent = NULL );
		~View();
		
		/**
		 * Unique String ID
		 */
		void setStringId( const QString& );
		const QString& getStringId();

		/**
		 * Volume to be displayed
		 */
		virtual void setVolume( vtkImageData* ) = 0;
		virtual vtkImageData* getVolume();

		virtual void init() = 0;
		virtual bool isInit();
	};
}

#endif
