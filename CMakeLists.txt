cmake_minimum_required(VERSION 3.0.0)

project(dream_engine)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(QT_USE_QTOPENGL ON)

find_package(Qt5Core)
find_package(Qt5Widgets)

include_directories("C:/Users/Eric/Documents/Visual Studio 2015/Projects/cpp/glm/")
	
	
file(GLOB SOURCE ./*.*)
add_executable(dream_engine ${SOURCE})

target_link_libraries(dream_engine Qt5::Core Qt5::Widgets)