cmake_minimum_required(VERSION 3.17)
project(app_complex_drawing CXX)


list(APPEND library_source
   _.cpp
   _.h
   _app_complex_drawing.h
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

elseif(LINUX OR FREEBSD)

   target_compile_options(app_complex_drawing PRIVATE -fpermissive)
   #target_link_options(app_complex_drawing PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_complex_drawing PRIVATE ${library_references})
   target_link_options(app_complex_drawing PRIVATE -Wl,-z,defs)

endif()



target_link_directories(app_complex_drawing PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_include_directories(app_complex_drawing PRIVATE ${library_include_directories})


target_compile_definitions(app_complex_drawing PRIVATE _APP_COMPLEX_DRAWING_LIBRARY)


add_executable(_${PROJECT_NAME} platform/${SLASHED_PLATFORM}/_${PROJECT_NAME}.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   app_complex_drawing)


if(LINUX OR FREEBSD)

   add_custom_command(
      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
      DEPENDS application_matter.txt matter.txt _console_application_build_helper
      VERBATIM
   )

   add_custom_target(${PROJECT_NAME}_matter
      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
      )

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()


if (MSVC)


   target_compile_options(_app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_drawing PRIVATE ${executable_references})


elseif(LINUX OR FREEBSD)


   target_compile_options(_app_complex_drawing PRIVATE -fpermissive)
   target_link_libraries(_app_complex_drawing PRIVATE ${executable_references})
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

set_target_properties(_app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)



