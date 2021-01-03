cmake_minimum_required(VERSION 3.17)
project(app_complex_drawing CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
   set(LINUX TRUE)
   set(PLATFORM_NAME "linux")
   include(FindPkgConfig)
elseif (WIN32)
   set(PLATFORM_NAME "windows")
endif ()


set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../time-${PLATFORM_NAME}/cmake)


list(APPEND app_complex_drawing_source
   _.h
   _drawing.h
   application.cpp
   application.h
   framework.cpp
   framework.h
   pane_view.cpp
   pane_view.h
   )


if (MSVC)
   set(LIBCXX_TARGETING_MSVC ON)
else ()
   set(LIBCXX_TARGETING_MSVC OFF)
endif ()


add_library(app_complex_drawing SHARED ${app_complex_drawing_source})

target_precompile_headers(app_complex_drawing PRIVATE framework.h)

set_target_properties(app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)


list(APPEND app_complex_drawing_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   app_simple_drawing
   )


if (MSVC)

   target_compile_options(app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_complex_drawing PRIVATE ${app_complex_drawing_references})
   add_dependencies(app_complex_drawing draw2d_gdiplus imaging_wic)

elseif (LINUX)

   target_compile_options(app_complex_drawing PRIVATE -fpermissive)
   target_link_options(app_complex_drawing PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(app_complex_drawing PRIVATE ${app_complex_drawing_references})
   target_link_options(app_complex_drawing PRIVATE -Wl,-z,defs)
   add_dependencies(app_complex_drawing draw2d_cairo imaging_freeimage)

endif ()


add_dependencies(app_complex_drawing experience_core)


list(APPEND library_link_directories
   ${LIBRARY_OUTPUT_PATH}
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/library/x64/basis
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/storage-${PLATFORM_NAME}/third/library/x64/basis
   )


target_link_directories(app_complex_drawing PRIVATE ${library_link_directories})


list(APPEND library_include_directories
   .
   $ENV{HOME}/__config
   ${CMAKE_CURRENT_SOURCE_DIR}/../..
   ${CMAKE_CURRENT_SOURCE_DIR}/..
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../source
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/app/_include
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../source/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/platform-${PLATFORM_NAME}/_include
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../../../archive/third-${PLATFORM_NAME}/third/include/include
   ${CMAKE_CURRENT_SOURCE_DIR}
   )


target_include_directories(app_complex_drawing PRIVATE ${library_include_directories})


target_compile_definitions(app_complex_drawing PRIVATE _APP_complex_DRAWING_LIBRARY)
target_compile_definitions(app_complex_drawing PRIVATE UNICODE)
target_compile_definitions(app_complex_drawing PRIVATE _UNICODE)

add_executable(_app_complex_drawing ${PLATFORM_NAME}/main.cpp)
target_compile_definitions(_app_complex_drawing PRIVATE UNICODE)
target_compile_definitions(_app_complex_drawing PRIVATE _UNICODE)


target_compile_definitions(_app_complex_drawing PRIVATE _APP_ID="app-complex/drawing")


if (MSVC)

   target_compile_options(_app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_drawing PRIVATE ${app_complex_drawing_references})
   add_dependencies(_app_complex_drawing draw2d_gdiplus imaging_wic)

elseif (LINUX)

   target_compile_options(_app_complex_drawing PRIVATE -fpermissive)
   target_link_options(_app_complex_drawing PRIVATE -Wl,-rpath=\$ORIGIN)
   target_link_libraries(_app_complex_drawing PRIVATE ${app_complex_drawing_references})
   target_link_options(_app_complex_drawing PRIVATE -Wl,-z,defs)
   add_dependencies(_app_complex_drawing draw2d_cairo imaging_freeimage)

endif ()

add_dependencies(_app_complex_drawing app_complex_drawing)

target_include_directories(_app_complex_drawing PRIVATE ${library_include_directories})

target_link_directories(_app_complex_drawing PRIVATE ${library_link_directories})

target_link_libraries(_app_complex_drawing PRIVATE acme apex)

set_target_properties(_app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)



