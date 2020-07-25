cmake_minimum_required(VERSION 3.16)
project(LangOCR)
include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})

file(GLOB GUI_SRC_FILES gui/*.cpp)
add_executable(LangOCR_GUI ${GUI_SRC_FILES})

file(GLOB SERVER_SRC_FILES server/*.cpp server/*.c lib/*.cpp)
add_executable(LangOCR_Server ${SERVER_SRC_FILES})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CONAN_INCLUDE_DIRS})
target_include_directories(LangOCR_Server PRIVATE .)

target_compile_options(LangOCR_GUI PRIVATE -fPIC)
target_link_libraries(LangOCR_GUI Qt5::Widgets)

target_link_libraries(LangOCR_Server ${CONAN_LIBS})
