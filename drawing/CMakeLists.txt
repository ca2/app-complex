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
   berg
   bred
   core
   app_simple_drawing
   )


add_library(${PROJECT_NAME} SHARED ${library_source})
add_library(static_${PROJECT_NAME} STATIC ${library_source})




if(${LINUX} OR ${__BSD__})


   add_custom_command(
      OUTPUT ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o
      COMMAND ${APPLICATION_BUILD_HELPER_BINARY} --prepare-application ${PROJECT_SOURCE_DIR}
      COMMENT "Generating ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o"
   )

   target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/.link_object/_matter.zip.o)

endif()





target_precompile_headers(${PROJECT_NAME} PRIVATE framework.h)
target_precompile_headers(static_${PROJECT_NAME} PRIVATE framework.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


if (MSVC)

   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})

elseif(${LINUX} OR ${__BSD__} OR ${ANDROID})

   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   #target_link_options(${PROJECT_NAME} PRIVATE -Wl,-rpath=$ORIGIN)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${library_references} ${global_library_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif()



target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})


list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND library_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${library_include_directories})
target_include_directories(static_${PROJECT_NAME} PRIVATE ${library_include_directories})



target_compile_definitions(${PROJECT_NAME} PRIVATE _${PROJECT_NAME}_project)


add_subdirectory(__implement)



