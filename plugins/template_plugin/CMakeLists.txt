project([name] CXX C)

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin)

find_package(OpenCV REQUIRED core imgproc highgui)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/[name].cpp ${PROJECT_SOURCE_DIR}/../../CV_wrapper/src/cv_plugin.cpp)
add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC
	 ${PROJECT_SOURCE_DIR}/include/ ${PROJECT_SOURCE_DIR}/../../CV_wrapper/include)

#OpenCV Libraries
target_link_Libraries(${PROJECT_NAME} ${OpenCV_LIBS})

