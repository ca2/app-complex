cmake_minimum_required(VERSION 3.16)
project(video_input CXX)


list(APPEND library_references
   acme
   apex
   aqua
   )

list(APPEND library_source
   _.h
   _struct.cpp
   _struct.h
   ##_library.h
   asynchronous_cache.h
   device.cpp
   device.h
   device_array.cpp
   device_array.h
   frame.cpp
   frame.h
   framework.cpp
   framework.h
   #graphics.h
   media_format.cpp
   media_format.h
   render.cpp
   render.h
   #video.h
   video_input.cpp
   video_input.h
   )




add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(video_input PRIVATE framework.h)

set_target_properties(video_input PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(video_input PRIVATE "/MD$<$<CONFIG:Debug>:d>")
    target_link_options(video_input PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
    target_link_options(video_input PRIVATE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(video_input PRIVATE ${library_references})
    target_link_libraries(video_input PRIVATE ws2_32 winmm shlwapi)
elseif(LINUX)
    target_compile_options(video_input PRIVATE -fpermissive)
    #target_link_options(video_input PRIVATE -Wl,-rpath=$ORIGIN)
    target_link_libraries(video_input PRIVATE pthread)
    target_link_libraries(video_input PRIVATE ${library_references})
    target_link_options(video_input PRIVATE -Wl,-z,defs)
endif()



list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(video_input PRIVATE _VIDEO_INPUT_LIBRARY)



