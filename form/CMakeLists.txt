cmake_minimum_required(VERSION 3.17)
project(app_complex_form CXX)


list(APPEND library_source
   _.cpp
   _.h
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
   pane_view.cpp
   pane_view.h
   )

add_library(app_complex_form ${library_source})


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


target_precompile_headers(app_complex_form PRIVATE framework.h)

set_target_properties(app_complex_form PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
   target_compile_options(app_complex_form PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_form PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_form PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_complex_form PRIVATE ${library_references})
   add_dependencies(app_complex_form draw2d_gdiplus imaging_wic)
elseif (LINUX)
   target_compile_options(app_complex_form PRIVATE -fpermissive)
   target_link_libraries(app_complex_form PRIVATE ${library_references})
   target_link_options(app_complex_form PRIVATE -Wl,-z,defs)
endif ()


add_dependencies(app_complex_form experience_tranquillum)
add_dependencies(app_complex_form ${default_draw2d})
add_dependencies(app_complex_form ${default_imaging})
add_dependencies(app_complex_form ${default_write_text})
add_dependencies(app_complex_form ${app_common_dependencies})
add_dependencies(app_complex_form database_sqlite3)
add_dependencies(app_complex_form regular_expression_pcre2)




target_include_directories(app_complex_form PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_include_directories(app_complex_form PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(app_complex_form PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_compile_definitions(app_complex_form PRIVATE _APP_COMPLEX_FORM_LIBRARY)


add_executable(_app_complex_form _app_complex_form.cpp)

target_include_directories(_app_complex_form PRIVATE ${library_include_directories})

target_link_directories(_app_complex_form PRIVATE ${library_link_directories})


list(APPEND executable_references
   acme
   apex
   app_complex_form
   )


if (MSVC)

   target_compile_options(_app_complex_form PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_form PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_form PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_form PRIVATE ${executable_references})

elseif (LINUX)

   target_compile_options(_app_complex_form PRIVATE -fpermissive)
   target_link_libraries(_app_complex_form PRIVATE ${executable_references})
   target_link_options(_app_complex_form PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(_app_complex_form ${default_draw2d})
add_dependencies(_app_complex_form ${default_imaging})
add_dependencies(_app_complex_form ${default_write_text})
add_dependencies(_app_complex_form ${default_gpu})
add_dependencies(_app_complex_form ${app_common_dependencies})
add_dependencies(_app_complex_form experience_core)


set_target_properties(_app_complex_form PROPERTIES LINKER_LANGUAGE CXX)



