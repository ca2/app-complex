cmake_minimum_required(VERSION 3.16)
project(app_complex_video_capture CXX)


list(APPEND library_source
   _.cpp
   _.h
   _library.h
   _factory.cpp
   application.cpp
   application.h
   device_selector.cpp
   device_selector.h
   document.cpp
   document.h
   edit_impact.cpp
   edit_impact.h
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
   toggle_impact.cpp
   toggle_impact.h
   top_impact.cpp
   top_impact.h
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
   video_input
   )


add_library(app_complex_video_capture SHARED ${library_source})

target_precompile_headers(app_complex_video_capture PRIVATE framework.h)

set_target_properties(app_complex_video_capture PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(app_complex_video_capture PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_video_capture PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_video_capture PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_complex_video_capture PRIVATE ${library_references})

elseif(LINUX OR FREEBSD)

   target_compile_options(app_complex_video_capture PRIVATE -fpermissive)
   #target_link_options(app_complex_video_capture PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_complex_video_capture PRIVATE ${library_references})
   target_link_options(app_complex_video_capture PRIVATE -Wl,-z,defs)

endif()



target_link_directories(app_complex_video_capture PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})


target_include_directories(app_complex_video_capture PRIVATE ${library_include_directories})


target_compile_definitions(app_complex_video_capture PRIVATE _app_complex_video_capture_LIBRARY)


add_executable(_${PROJECT_NAME} _main.cpp)


list(APPEND executable_references
   acme
   apex
   aqua
   aura
   axis
   base
   bred
   core
   app_complex_video_capture)


if(LINUX OR FREEBSD)

#   add_custom_command(
#      COMMAND ${APPLICATION_BUILD_HELPER} ${PROJECT_SOURCE_DIR}
#      COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/matter.timestamp
#      OUTPUT ${PROJECT_BINARY_DIR}/matter.timestamp
#      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#      BYPRODUCTS ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
#      DEPENDS application_matter.txt matter.txt _console_application_build_helper
#      VERBATIM
#   )
#
#   add_custom_target(${PROJECT_NAME}_matter
#      DEPENDS ${PROJECT_BINARY_DIR}/matter.timestamp
#      )

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

#   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()


if (MSVC)


   target_compile_options(_app_complex_video_capture PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_video_capture PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(_app_complex_video_capture PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(_app_complex_video_capture PRIVATE ${executable_references})


elseif(LINUX OR FREEBSD)


   target_compile_options(_app_complex_video_capture PRIVATE -fpermissive)
   target_link_libraries(_app_complex_video_capture PRIVATE ${executable_references})
   target_link_options(_app_complex_video_capture PRIVATE -Wl,-z,defs)


endif ()


add_dependencies(_app_complex_video_capture experience_core)
add_dependencies(_app_complex_video_capture ${default_draw2d})
add_dependencies(_app_complex_video_capture ${default_imaging})
add_dependencies(_app_complex_video_capture ${default_write_text})
add_dependencies(_app_complex_video_capture ${app_common_dependencies})
add_dependencies(_app_complex_video_capture database_sqlite3)


if(LINUX)

   add_dependencies(_app_complex_video_capture video_input_video_for_linux)

endif()

target_include_directories(_app_complex_video_capture PRIVATE ${library_include_directories})

target_link_directories(_app_complex_video_capture PRIVATE ${library_link_directories})

set_target_properties(_app_complex_video_capture PROPERTIES LINKER_LANGUAGE CXX)



