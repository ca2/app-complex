cmake_minimum_required(VERSION 3.16)
project(app_complex_drawing CXX)


list(APPEND library_source
   _.cpp
   _.h
   ##_library.h
   #_factory.cpp
   application.cpp
   application.h
   framework.cpp
   framework.h
   pane_impact.cpp
   pane_impact.h
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


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})

target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(app_complex_drawing PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(app_complex_drawing PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(app_complex_drawing PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(app_complex_drawing PRIVATE ${library_references})

elseif(${LINUX} OR ${FREEBSD})

   target_compile_options(app_complex_drawing PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   #target_link_options(app_complex_drawing PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(app_complex_drawing PRIVATE ${library_references})
   target_link_options(app_complex_drawing PRIVATE -Wl,-z,defs)

endif()



target_link_directories(app_complex_drawing PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(app_complex_drawing PRIVATE _APP_COMPLEX_DRAWING_LIBRARY)


add_subdirectory(__implement)



