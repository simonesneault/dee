#include "deeView3D.h"

#include "vtkColorTransferFunction.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkPiecewiseFunction.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkVolume.h"

namespace dee{
	View3D::View3D( QWidget* a_parent ) : View( a_parent ){
		m_volume_mapper = vtkGPUVolumeRayCastMapper::New();	
		m_volume_property = vtkVolumeProperty::New();		 
		m_opacity = vtkPiecewiseFunction::New(); 
		m_color = vtkColorTransferFunction::New(); 
		m_volume = vtkVolume::New();
		m_renderer = vtkRenderer::New();
	}
	
	View3D::~View3D(){
		m_volume_mapper->Delete();
		m_volume_property->Delete();
		m_opacity->Delete();
		m_color->Delete();
		m_volume->Delete();
		m_renderer->Delete();
	}

	
	void View3D::setImageData( vtkImageData* a_image_data ){
		
		m_image_data = a_image_data;
		Q_ASSERT( m_image_data );

		this->init();

		m_volume_mapper->SetInputData( m_image_data );

		m_opacity->AddPoint(0.0,0.0);
		m_opacity->AddPoint(80.0,1.0);
		m_opacity->AddPoint(80.1,0.0);
		m_opacity->AddPoint(255.0,0.0);
		m_color->AddRGBPoint(0.0  ,0.0,0.0,1.0);
		m_color->AddRGBPoint(40.0  ,1.0,0.0,0.0);
		m_color->AddRGBPoint(255.0,1.0,1.0,1.0);
		m_volume->SetMapper( m_volume_mapper );
		m_volume->SetProperty( m_volume_property );

		m_renderer->AddVolume( m_volume );
		
	}

	void View3D::init(){
		if( m_is_init )
			return;
		m_is_init = true;
		this->GetRenderWindow()->AddRenderer( m_renderer );
		m_volume_mapper->SetBlendModeToComposite();
		m_volume_mapper->AutoAdjustSampleDistancesOn();
		m_volume_mapper->SetMaxMemoryFraction( 0.9 );

		m_volume_property->SetScalarOpacity( m_opacity ); 
		m_volume_property->SetColor( m_color );
	}

}