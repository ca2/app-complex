cmake_minimum_required(VERSION 3.16)
project(app_complex_form CXX)


list(APPEND library_source
   _.cpp
   _.h
   #_factory.cpp
   application.cpp
   application.h
   document.cpp
   document.h
   form.cpp
   form.h
   form_001.cpp
   form_001.h
   form_002.cpp
   form_002.h
   frame.cpp
   frame.h
   framework.cpp
   framework.h
   impact.cpp
   impact.h
   main_frame.cpp
   main_frame.h
   main_impact.cpp
   main_impact.h
   pane_impact.cpp
   pane_impact.h
   )

add_library(${PROJECT_NAME} ${library_source})


list(APPEND library_references
   acme
   apex
   aqua
   aura
   axis
   base
   app_simple_form
   bred
   core
   )


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   add_dependencies(${PROJECT_NAME} draw2d_gdiplus imaging_wic)
elseif(LINUX OR FREEBSD)
   target_compile_options(${PROJECT_NAME} PRIVATE -fpermissive)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _APP_COMPLEX_FORM_LIBRARY)


add_subdirectory(__implement)

