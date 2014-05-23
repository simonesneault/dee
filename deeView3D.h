#ifndef deeView3D_H
#define deeView3D_H

#include "deeView.h"

namespace dee{
	class View3D : public View{

		Q_OBJECT

	public:
		View3D( QWidget* a_parent = NULL );
		virtual ~View3D();

		virtual void setVolume( vtkImageData* );
		virtual void init();

	};
}

#endif // deeView3D_H
