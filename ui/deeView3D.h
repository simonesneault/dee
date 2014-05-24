#ifndef DEE_VIEW_3D_H
#define DEE_VIEW_3D_H

#include "deeView.h"

namespace dee{
	class View3D : public View{

		Q_OBJECT

	protected:

		vtkGPUVolumeRayCastMapper*	m_volume_mapper;
		vtkVolumeProperty*			m_volume_property;
		vtkVolume*					m_volume;
		vtkPiecewiseFunction*		m_opacity;
		vtkColorTransferFunction*	m_color;
		vtkRenderer*				m_renderer;


	public:
		View3D( QWidget* a_parent = NULL );
		virtual ~View3D();

		virtual void setImageData( vtkImageData* );
		virtual void init();

	};
}

#endif
