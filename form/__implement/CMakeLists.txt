cmake_minimum_required(VERSION 3.16)
project(_app_complex_form CXX)



add_executable(${PROJECT_NAME} application_main.cpp)

list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/..)
list(APPEND executable_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/../..)

target_include_directories(${PROJECT_NAME} PRIVATE ${executable_include_directories})


target_link_directories(${PROJECT_NAME} PRIVATE ${library_link_directories})


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


if(${LINUX} OR ${__BSD__})

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

   list(APPEND executable_references ${PROJECT_SOURCE_DIR}/../.link_object/_matter.zip.o)

#   add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_matter)

endif()


add_dependencies(${PROJECT_NAME} folder_zip)


if (MSVC)

   target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/DEFAULTLIB:msvcrt$<$<CONFIG:Debug>:d>")
   target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})

elseif(${LINUX} OR ${__BSD__})

   target_compile_options(${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive  ${EXTRA_CXX_TARGET_COMPILER_OPTIONS}>)
   target_link_libraries(${PROJECT_NAME} PRIVATE ${executable_references})
   target_link_options(${PROJECT_NAME} PRIVATE -Wl,-z,defs)

endif ()


add_dependencies(${PROJECT_NAME} ${default_draw2d})
add_dependencies(${PROJECT_NAME} ${default_imaging})
add_dependencies(${PROJECT_NAME} ${default_write_text})
add_dependencies(${PROJECT_NAME} ${app_common_dependencies})
add_dependencies(${PROJECT_NAME} crypto_openssl)
add_dependencies(${PROJECT_NAME} database_sqlite3)
add_dependencies(${PROJECT_NAME} experience_tranquillum)


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)



