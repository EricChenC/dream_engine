cmake_minimum_required(VERSION 3.0.0)

project(dream_engine)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(QT_USE_QTOPENGL ON)

find_package(Qt5 REQUIRED)

include_directories("C:/Users/Eric/Documents/Visual Studio 2015/Projects/cpp/glm/")

set(SOURCES
	main.cpp 
	dopenglwidget.cpp 
	dmainview.cpp 
	dmainmodel.cpp 
	dview.cpp 
	shadow.cpp 
	dmaterialview.cpp 
	dmaterialmodel.cpp 
	dmodel.cpp 
	dplayercamera.cpp 
	dshader.cpp 
	dshadertoyview.cpp 
	dshadertoymodel.cpp 
	dtexture.cpp
	ddir.cpp )

add_executable(dream_engine WIN32 ${SOURCES})

target_link_libraries(dream_engine Qt5::Core)