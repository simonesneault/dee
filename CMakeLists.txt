cmake_minimum_required( VERSION 2.8.8 )
if( POLICY CMP0020 )
	cmake_policy( SET CMP0020 NEW )
endif()
if( POLICY CMP0025 )
	cmake_policy( SET CMP0025 NEW ) # CMake 3.0
endif()


project( dee3 )

# find VTK
find_package( VTK COMPONENTS
	vtkCommonCore
	vtkFiltersSources
	vtkGUISupportQt
	vtkIOImage
	vtkInteractionImage
)
include( ${VTK_USE_FILE} )


if( "${VTK_QT_VERSION}" STREQUAL "" )
	message( FATAL_ERROR "VTK was not built with Qt ")
endif()

# Set your files and resources here
set( DEE_SRC dee3.cpp deeMainWindow.cpp )
set( DEE_H deeMainWindow.h )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

find_package( Qt5Widgets REQUIRED QUIET )
qt5_wrap_cpp( DEE_MOC_SRC ${DEE_H} )

add_executable( dee3 ${DEE_SRC} ${DEE_H} ${DEE_MOC_SRC} )
qt5_use_modules( dee3 Core Gui Widgets )
target_link_libraries( dee3 ${VTK_LIBRARIES} )

