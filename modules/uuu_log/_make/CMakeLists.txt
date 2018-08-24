#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/modules/uuu_log" path-module-uuu_log )
file( GLOB_RECURSE files-module-uuu_log "${path-module-uuu_log}" "${path-module-uuu_log}/*.cpp" )

add_library( module-uuu_log SHARED ${files-module-uuu_log} )

set_target_properties(      module-uuu_log  PROPERTIES  OUTPUT_NAME "mpl_uuu_log" )
target_compile_definitions( module-uuu_log  PUBLIC      ${shared_compile_def} )
target_compile_options(     module-uuu_log  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  target_link_libraries( module-uuu_log
  android
  ${log-lib} )
 endif()

target_link_libraries( module-uuu_log
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  optim-lib
  ${all-event-libs}
  ${shared_link_flags} )
