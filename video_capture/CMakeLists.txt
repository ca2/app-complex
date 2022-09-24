cmake_minimum_required(VERSION 3.16)
project(app_complex_video_capture CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   #_factory.cpp
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


add_library(${PROJECT_NAME} SHARED ${library_source})

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


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(app_complex_video_capture PRIVATE _APP_COMPLEX_VIDEO_CAPTURE_LIBRARY)


add_subdirectory(__implement)

