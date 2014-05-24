cmake_minimum_required( VERSION 2.8.8 )
if( POLICY CMP0020 )
	cmake_policy( SET CMP0020 NEW )
endif()
if( POLICY CMP0025 )
	cmake_policy( SET CMP0025 NEW ) # CMake 3.0
endif()

################# 
# dee3 project !
#################
project( dee3 )

# find and includes VTK
find_package( VTK COMPONENTS
	vtkCommonCore
	vtkFiltersSources
	vtkGUISupportQt
	vtkIOImage
	vtkInteractionImage
	vtkRenderingOpenGL
)
include( ${VTK_USE_FILE} )
if( "${VTK_QT_VERSION}" STREQUAL "" )
	message( FATAL_ERROR "VTK was not built with Qt ")
endif()

#platform specific options :
if( WIN32 OR WIN64 )
	add_definitions( /MP )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
endif()



# find and includes Qt5
find_package( Qt5Widgets REQUIRED QUIET )


include_directories( 
	${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR}/core/
	${CMAKE_CURRENT_SOURCE_DIR}/ui/
	${CMAKE_CURRENT_SOURCE_DIR}/io/ )

# Glob all files here for now
file( GLOB DEE_SRC 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/io/*.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp" )
file( GLOB DEE_H 
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/core/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/io/*.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/ui/*.h" )

# Generate _moc files 
qt5_wrap_cpp( DEE_MOC_SRC ${DEE_H} )

# Create dee3 executable
add_executable( dee3 ${DEE_SRC} ${DEE_H} ${DEE_MOC_SRC} )
qt5_use_modules( dee3 Core Gui Widgets Svg Xml )
target_link_libraries( dee3 ${VTK_LIBRARIES} )

