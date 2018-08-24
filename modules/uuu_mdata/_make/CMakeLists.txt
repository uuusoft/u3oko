#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/modules/uuu_mdata" path-module-uuu_mdata )
file( GLOB_RECURSE files-module-uuu_mdata "${path-module-uuu_mdata}" "${path-module-uuu_mdata}/*.cpp" )

add_library( module-uuu_mdata SHARED ${files-module-uuu_mdata} )

set_target_properties(      module-uuu_mdata PROPERTIES OUTPUT_NAME "mpl_uuu_mdata" )
target_compile_definitions( module-uuu_mdata PUBLIC ${shared_compile_def} )
target_compile_options(     module-uuu_mdata PUBLIC ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
 target_link_libraries( module-uuu_mdata
  android
  app-glue
  cpufeatures-lib
  ${log-lib} )
endif()

target_link_libraries( module-uuu_mdata
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
