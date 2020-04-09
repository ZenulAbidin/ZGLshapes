cmake_minimum_required(VERSION 3.1.0)

project(ZGLshapes VERSION 1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)

list(APPEND ZGLshapes_tests_BASE
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_base
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)


add_executable(test_z_qtshapes_base ${ZGLshapes_SOURCES} ${ZGLshapes_tests_BASE} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_base zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )
