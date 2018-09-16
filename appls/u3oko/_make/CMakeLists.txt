#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/appls/u3oko" path-appl-u3oko )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  file( GLOB_RECURSE files-appl-u3oko "${path-appl-u3oko}" "${path-appl-u3oko}/*.cpp" )
else()
  file( GLOB files-appl-u3oko "${path-appl-u3oko}" "${path-appl-u3oko}/*.cpp" "${path-appl-u3oko}/appl/*.cpp" )
endif()

add_library( appl-u3oko SHARED ${files-appl-u3oko} )

set_target_properties(      appl-u3oko  PROPERTIES  OUTPUT_NAME "appl_u3oko" )
target_compile_definitions( appl-u3oko  PUBLIC      ${shared_compile_def} )
target_compile_options(     appl-u3oko  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}> )

target_link_libraries( appl-u3oko
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
