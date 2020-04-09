cmake_minimum_required(VERSION 3.1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)


list(APPEND ZGLshapes_tests_QELLIPSE_1
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_1
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_1 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_1} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_1 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_2
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_2
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_2 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_2} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_2 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_3
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_3
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_3 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_3} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_3 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_4
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_4
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_4 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_4} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_4 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_5
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_5
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_5 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_5} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_5 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_6
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_6
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_6 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_6} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_6 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_7
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_7
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_7 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_7} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_7 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_8
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_8
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_8 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_8} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_8 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QELLIPSE_9
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qellipse_9
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qellipse_9 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QELLIPSE_9} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qellipse_9 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )
