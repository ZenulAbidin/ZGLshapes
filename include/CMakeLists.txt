cmake_minimum_required(VERSION 3.1.0)

project(ZGLshapes VERSION 1.0)

set(INCLUDE_FILES z_base.h z_qpoint.h z_qline.h z_qtri.h z_qrect.h z_qellipse.h)

list(APPEND ZGLshapes_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/z_base.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qpoint.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qline.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qtri.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qrect.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qellipse.h
)
list(APPEND ZGLshapes_Boost_INCLUDES
    ${Boost_INCLUDE_DIRS}/boost/geometry.hpp
    ${Boost_INCLUDE_DIRS}/boost/geometry/geometries/register/point.hpp
)

install(FILES ${ZGLshapes_INCLUDES} DESTINATION include)
