cmake_minimum_required(VERSION 3.10)
project(IN2OSM)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Modules;${CMAKE_MODULE_PATH}" )

# include_directories("C:/Users/byeonggon/rapidxml-1.13")

file(GLOB INDOOR_FILES
        "IndoorGML_Reader/*.h"
        "IndoorGML_Reader/*.cpp"
        "IndoorGML_Writer/*.h"
        "IndoorGML_Writer/*.cpp"
        )

file(GLOB OSM_FILES
        "OSM_Reader/*.h"
        "OSM_Reader/*.cpp"
        "OSM_Writer/*.h"
        "OSM_Writer/*.cpp"
        )
file(GLOB TRANSFORM_FILES
        "transform/*.h"
        )
file(GLOB IO_FILES
        "IO/*.h"
        "IO/*.cpp"
        )
add_executable(IN2OSM
        ${INDOOR_FILES}
        ${OSM_FILES}
        ${TRANSFORM_FILES}
        ${IO_FILES}
        CONVERTER.cpp DOC/mainpage.h)
include_directories("../IN2OSM")