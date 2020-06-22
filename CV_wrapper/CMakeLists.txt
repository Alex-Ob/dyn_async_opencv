project(CVwrapperTest CXX)

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

find_package(OpenCV REQUIRED core imgproc highgui)

set(SRC_LIST ${PROJECT_SOURCE_DIR}/src/test.cpp ${PROJECT_SOURCE_DIR}/src/CV_wrapper.cpp ${PROJECT_SOURCE_DIR}/src/cv_plugin.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})

message("PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})
message("CMAKE_PROJECT_NAME: " ${CMAKE_PROJECT_NAME})
message("PROJECT_NAME: " ${PROJECT_NAME})
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
message("OpenCV_INCLUDE_DIRS: " ${OpenCV_INCLUDE_DIRS})
message("OpenCV_LIBS: " ${OpenCV_LIBS})


target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

#OpenCV Libraries
target_link_Libraries(${PROJECT_NAME} ${OpenCV_LIBS})
# dlopen, dlsym etc.
target_link_libraries(${PROJECT_NAME} libdl.so)
