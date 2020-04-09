cmake_minimum_required(VERSION 3.1.0)

project(ZGLshapes VERSION 1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)


list(APPEND ZGLshapes_tests_QTRI_1
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_1
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_1 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_1} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_1 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_2
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_2
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_2 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_2} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_2 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_3
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_3
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_3 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_3} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_3 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_4
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_4
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_4 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_4} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_4 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_5
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_5
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_5 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_5} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_5 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_6
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_6
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_6 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_6} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_6 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_7
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_7
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_7 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_7} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_7 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_8
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_8
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_8 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_8} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_8 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QTRI_9
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qtri_9
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qtri_9 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QTRI_9} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qtri_9 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )
