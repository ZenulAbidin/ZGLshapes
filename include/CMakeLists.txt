cmake_minimum_required(VERSION 3.1.0)

#set(INCLUDE_FILES z_base.h z_qpoint.h z_qline.h z_qtri.h z_qrect.h z_qellipse.h)
#TODO this includes list is passed to all the files. It is certainly not the case
# that all of these header files are needed by each source file.
list(APPEND ZGLshapes_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/z_base.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qpoint.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qline.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qtri.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qrect.h
    ${CMAKE_CURRENT_LIST_DIR}/z_qellipse.h
    ${CMAKE_CURRENT_LIST_DIR}/z_linalg.h
    ${CMAKE_CURRENT_LIST_DIR}/z_geometry_util.h
)

list(APPEND ZGLshapes_Boost_INCLUDES
    ${Boost_INCLUDE_DIRS}/boost/geometry.hpp
    ${Boost_INCLUDE_DIRS}/boost/geometry/geometries/register/point.hpp
)

install(FILES ${ZGLshapes_INCLUDES} DESTINATION include)
