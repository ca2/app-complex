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
elseif(LINUX OR FREEBSD)
   target_compile_options(app_complex_form PRIVATE -fpermissive)
   target_link_libraries(app_complex_form PRIVATE ${library_references})
   target_link_options(app_complex_form PRIVATE -Wl,-z,defs)
endif ()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(app_complex_form PRIVATE _APP_COMPLEX_FORM_LIBRARY)


add_executable(_${PROJECT_NAME} platform/${SLASHED_PLATFORM}/_${PROJECT_NAME}.cpp)

target_include_directories(_app_complex_form PRIVATE ${library_include_directories})

target_link_directories(_app_complex_form PRIVATE ${library_link_directories})


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   app_complex_form
   )


if(LINUX OR FREEBSD)

   add_custom_command(
      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
      DEPENDS application_matter.txt deps.txt matter.txt _console_application_build_helper
      VERBATIM
   )

   add_custom_target(${PROJECT_NAME}_matter
      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
      )

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()


add_dependencies(_${PROJECT_NAME} folder_zip)


if (MSVC)

   target_compile_options(_app_complex_form PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_form PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_form PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_form PRIVATE ${executable_references})

elseif(LINUX OR FREEBSD)

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



