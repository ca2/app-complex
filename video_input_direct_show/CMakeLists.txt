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
        platform.cpp
        platform.h
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

target_precompile_headers(${PROJECT_NAME} PRIVATE platform.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE platform.h)

set_target_properties(draw2d_gdiplus PROPERTIES LINKER_LANGUAGE CXX)

if(${WIN32})


   if(MSVC)


      target_compile_options(${PROJECT_NAME} PRIVATE     "/MD$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE     "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
      target_link_options(${PROJECT_NAME} PRIVATE     "/SUBSYSTEM:WINDOWS")
      target_link_options(${PROJECT_NAME} PRIVATE     "/bigobj")
      target_link_options(${PROJECT_NAME} PRIVATE     "/IMPLIB:${LIBRARY_OUTPUT_PATH}/${PROJECT_NAME}.lib")
      target_link_options(${PROJECT_NAME} PRIVATE     "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   else()


      target_link_options(${PROJECT_NAME} PRIVATE "-mwindows")
      target_sources(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.def")


   endif()

    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif(${LINUX})
       target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
    #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_libraries(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
    message(STATUS "PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
