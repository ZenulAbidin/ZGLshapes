cmake_minimum_required(VERSION 3.1.0)

project(ZGLshapes VERSION 1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)

list(APPEND ZGLshapes_tests_LINALG
    ${CMAKE_CURRENT_LIST_DIR}/test_z_linalg
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)


add_executable(test_z_linalg ${ZGLshapes_SOURCES} ${ZGLshapes_tests_LINALG} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_linalg zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )



list(APPEND ZGLshapes_tests_MATRIX
    ${CMAKE_CURRENT_LIST_DIR}/test_z_matrix
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)


add_executable(test_z_matrix ${ZGLshapes_SOURCES} ${ZGLshapes_tests_MATRIX} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_matrix zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_OFFSETMATRIX
    ${CMAKE_CURRENT_LIST_DIR}/test_z_offsetmatrix
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)


add_executable(test_z_offsetmatrix ${ZGLshapes_SOURCES} ${ZGLshapes_tests_OFFSETMATRIX} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_offsetmatrix zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_MATRIXTRAITS
    ${CMAKE_CURRENT_LIST_DIR}/test_z_matrixtraits
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)


add_executable(test_z_matrixtraits ${ZGLshapes_SOURCES} ${ZGLshapes_tests_MATRIXTRAITS} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_matrixtraits zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )

