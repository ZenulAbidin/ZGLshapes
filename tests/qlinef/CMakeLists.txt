cmake_minimum_required(VERSION 3.1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)


list(APPEND ZGLshapes_tests_QLINEF_1
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_1
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_1 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_1} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_1 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_2
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_2
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_2 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_2} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_2 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_3
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_3
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_3 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_3} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_3 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_4
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_4
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_4 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_4} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_4 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_5
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_5
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_5 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_5} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_5 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_6
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_6
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_6 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_6} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_6 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )


list(APPEND ZGLshapes_tests_QLINEF_7
    ${CMAKE_CURRENT_LIST_DIR}/test_z_qtshapes_qlinef_7
    ${Boost_INCLUDE_DIRS}/boost/test/included/unit_test.hpp
)

add_executable(test_z_qtshapes_qlinef_7 ${ZGLshapes_SOURCES} ${ZGLshapes_tests_QLINEF_7} )
link_directories(Boost_LIBRARY_DIRS)
target_link_libraries(test_z_qtshapes_qlinef_7 zglshapes2d boost_system-mt Qt5::Widgets)
target_include_directories(zglshapes2d
          PRIVATE ${Boost_INCLUDE_DIRS}
          )

