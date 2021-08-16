cmake_minimum_required(VERSION 3.17)
project(app_complex_drawing CXX)


list(APPEND library_source
   _.cpp
   _.h
   _drawing.h
   application.cpp
   application.h
   framework.cpp
   framework.h
   pane_view.cpp
   pane_view.h
   )


list(APPEND library_references
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


add_library(app_complex_drawing SHARED ${library_source})

target_precompile_headers(app_complex_drawing PRIVATE framework.h)

set_target_properties(app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_complex_drawing PRIVATE ${library_references})

elseif (LINUX)

   target_compile_options(app_complex_drawing PRIVATE -fpermissive)
   #target_link_options(app_complex_drawing PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_complex_drawing PRIVATE ${library_references})
   target_link_options(app_complex_drawing PRIVATE -Wl,-z,defs)

endif()



target_link_directories(app_complex_drawing PRIVATE ${library_link_directories})


target_include_directories(app_complex_drawing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_complex_drawing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_complex_drawing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(app_complex_drawing PRIVATE ${library_include_directories})


target_compile_definitions(app_complex_drawing PRIVATE _APP_COMPLEX_DRAWING_LIBRARY)


add_executable(_app_complex_drawing ${PLATFORM_NAME}/main.cpp)


target_compile_definitions(_app_complex_drawing PRIVATE _APP_ID="app-complex/drawing")


if (MSVC)

   target_compile_options(_app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_drawing PRIVATE acme apex app_complex_drawing)

elseif (LINUX)

   target_compile_options(_app_complex_drawing PRIVATE -fpermissive)
   #target_link_options(_app_complex_drawing PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(_app_complex_drawing PRIVATE acme apex app_complex_drawing)
   target_link_options(_app_complex_drawing PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_complex_drawing experience_core)
add_dependencies(_app_complex_drawing ${default_draw2d})
add_dependencies(_app_complex_drawing ${default_imaging})
add_dependencies(_app_complex_drawing ${default_write_text})
add_dependencies(_app_complex_drawing ${app_common_dependencies})
add_dependencies(_app_complex_drawing database_sqlite3)


target_include_directories(_app_complex_drawing PRIVATE ${library_include_directories})

target_link_directories(_app_complex_drawing PRIVATE ${library_link_directories})

target_link_libraries(_app_complex_drawing PRIVATE acme apex)

set_target_properties(_app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)



