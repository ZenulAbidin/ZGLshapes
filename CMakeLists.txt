cmake_minimum_required(VERSION 3.1.0)

project(ZGLshapes VERSION 1.1.1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#FIXME is this still needed?
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(ZGLSHAPES_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)

set(ZGLSHAPES_INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(ZGLSHAPES_INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(ZGLSHAPES_INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)

#include_directories(${ZGLSHAPES_HEADERS_DIR})
#file(COPY run-tests.sh DESTINATION .) 

SET(NO_TESTS false CACHE BOOL "Explicitly supress all tests")
SET(ALL_TESTS true CACHE BOOL "Explicitly enable all tests")

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost REQUIRED)

if(!Boost_geometry_FOUND)
message(FATAL_ERROR "Boost.Geometry not found")
endif()

if(!Boost_test_FOUND)
message(FATAL_ERROR "Boost.Test not found")
endif()

# Use -DBOOST_ROOT to insert a prefix to search in

add_subdirectory(include)
add_subdirectory(src)

if(NO_TESTS)
message("Supressing all tests")
else()
add_subdirectory(tests)
endif()

