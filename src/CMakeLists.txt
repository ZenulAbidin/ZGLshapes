cmake_minimum_required(VERSION 3.1.0)

include(${ZGLSHAPES_HEADERS_DIR}/CMakeLists.txt)

list(APPEND ZGLshapes_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/z_qpoint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/z_qline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/z_qtri.cpp
    ${CMAKE_CURRENT_LIST_DIR}/z_qrect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/z_qellipse.cpp
)


#set(SOURCE_FILES z_qpoint.cpp z_qline.cpp z_qtri.cpp z_qrect.cpp z_qellipse.cpp)

add_library(zglshapes2d SHARED ${ZGLshapes_SOURCES})
target_link_libraries(zglshapes2d Qt5::Widgets)
target_include_directories(zglshapes2d
          PUBLIC ${ZGLSHAPES_HEADERS_DIR}
          )
target_include_directories(zglshapes2d
            PUBLIC ${Boost_INCLUDE_DIRS}
)

install(TARGETS zglshapes2d DESTINATION lib)
