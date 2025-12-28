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
   #udev.cpp
   #udev.h
   video_input.cpp
   video_input.h
   )


add_library(${PROJECT_NAME} SHARED ${library_source})


add_library(static_${PROJECT_NAME} STATIC ${library_source})


target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(${WIN32})
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(${PROJECT_NAME} PRIVATE "/IMPLIB:${LIBRARY_OUTPUT_PATH}/video_input_video_for_linux.lib")
    target_link_options(${PROJECT_NAME} PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/video_input_video_for_linux.def")
    target_link_libraries(${PROJECT_NAME} PRIVATE acme apex aqua aura Gdiplus)
elseif(${LINUX} OR ${__BSD__} OR ${ANDROID})

   #if(${USE_PKGCONFIG})
      pkg_check_modules(${PROJECT_NAME}_PKGCONFIG libavcodec libswscale libavformat libavutil libv4l2)
   #endif()
   target_compile_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_compile_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_CFLAGS})
   target_link_options(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   target_link_options(static_${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_PKGCONFIG_LDFLAGS})
   #target_link_options(video_input_video_for_linux PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references} ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)
   message(STATUS "PKGCONFIG_LIBRARIES is " ${${PROJECT_NAME}_PKGCONFIG_LIBRARIES})
   
endif()


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)


target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})


target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)
