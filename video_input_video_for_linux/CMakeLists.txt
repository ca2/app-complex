cmake_minimum_required(VERSION 3.16)
project(video_input_video_for_linux CXX)

list(APPEND library_references
   acme
   apex
   aqua
   aura
   video_input
   )

list(APPEND library_source
   _.h
        #_function.h
   _factory.cpp
   _struct.cpp
   #_video_input_video_for_linux.h
   callback.cpp
   callback.h
   device.cpp
   device.h
   framework.cpp
   framework.h
   helpers.cpp
   helpers.h
   mjpeg_decoder.cpp
   mjpeg_decoder.h
   render.cpp
   render.h
   thread.cpp
   thread.h
   udev.cpp
   udev.h
   video_input.cpp
   video_input.h
   )


add_library(video_input_video_for_linux SHARED ${library_source} )

target_precompile_headers(video_input_video_for_linux PRIVATE framework.h)

set_target_properties(video_input_video_for_linux PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(video_input_video_for_linux PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(video_input_video_for_linux PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(video_input_video_for_linux PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/video_input_video_for_linux.lib")
    target_link_options(video_input_video_for_linux PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/video_input_video_for_linux.def")
    target_link_libraries(video_input_video_for_linux PRIVATE acme apex aqua aura Gdiplus)
elseif(LINUX)

   if(NOT DONT_USE_PKG_CONFIG)
      pkg_check_modules(PKGCONFIG libavcodec libswscale libavformat libavutil libv4l2 libudev)
   endif()
   target_compile_options(video_input_video_for_linux PRIVATE ${PKGCONFIG_CFLAGS})
   target_link_options(video_input_video_for_linux PRIVATE ${PKGCONFIG_LDFLAGS})
   #target_link_options(video_input_video_for_linux PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(video_input_video_for_linux PRIVATE ${library_references} ${PKGCONFIG_LIBRARIES})
   target_link_options(video_input_video_for_linux PRIVATE -Wl,-z,defs)
   message("PKGCONFIG_LIBRARIES is " ${PKGCONFIG_LIBRARIES})
   
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(video_input_video_for_linux PRIVATE _VIDEO_INPUT_VIDEO_FOR_LINUX_LIBRARY)
