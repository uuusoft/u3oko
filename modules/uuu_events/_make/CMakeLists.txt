#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/modules/uuu_events" path-module-uuu_events )
file( GLOB_RECURSE files-module-uuu_events "${path-module-uuu_events}" "${path-module-uuu_events}/*.cpp" )

add_library( module-uuu_events SHARED ${files-module-uuu_events} )

set_target_properties(      module-uuu_events   PROPERTIES  OUTPUT_NAME "mpl_uuu_events" )
target_compile_definitions( module-uuu_events   PUBLIC      ${shared_compile_def} )
target_compile_options(     module-uuu_events   PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  target_link_libraries( module-uuu_events  
    android
    ${log-lib} )
endif()

target_link_libraries( module-uuu_events  
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  optim-lib
  ${all-event-libs}
  sqlite-lib
  ${shared_link_flags} )
 