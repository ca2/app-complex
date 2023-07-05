cmake_minimum_required(VERSION 3.16)
project(draw2d_gdiplus CXX)


list(APPEND library_source
        _.cpp
        _.h
        bitmap.cpp
        bitmap.h
        brush.cpp
        brush.h
        _factory.cpp
        font.cpp
        font.h
        framework.cpp
        framework.h
        graphics.cpp
        graphics.h
        image.cpp
        image.h
        object.cpp
        object.h
        path.cpp
        path.h
        pen.cpp
        pen.h
        thumbnail_dc.cpp
        region.cpp
        region.h
        text.cpp)

add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(draw2d_gdiplus PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(draw2d_gdiplus PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_gdiplus PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(draw2d_gdiplus PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/draw2d_gdiplus.lib")
    target_link_options(draw2d_gdiplus PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/draw2d_gdiplus.def")
    target_link_libraries(draw2d_gdiplus PRIVATE acme apex aqua aura Gdiplus)
elseif(${LINUX})
       target_compile_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
target_compile_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LDFLAGS})
    #target_link_options(draw2d_gdiplus PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${PKGCONFIG_LIBRARIES})
    target_link_options(draw2d_gdiplus PRIVATE -Wl,-z,defs)
    message(STATUS "PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(draw2d_gdiplus PRIVATE _DRAW2D_GDIPLUS_LIBRARY)
