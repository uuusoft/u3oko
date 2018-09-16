#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/modules/uuu_storage" path-module-uuu_storage )
file( GLOB_RECURSE files-module-uuu_storage "${path-module-uuu_storage}" "${path-module-uuu_storage}/*.cpp" )

add_library( module-uuu_storage SHARED ${files-module-uuu_storage} )

set_target_properties(      module-uuu_storage  PROPERTIES  OUTPUT_NAME "mpl_uuu_storage" )
target_compile_definitions( module-uuu_storage  PUBLIC      ${shared_compile_def} )
target_compile_options(     module-uuu_storage  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( module-uuu_storage
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  optim-lib
  ${all-event-libs}
  sqlite-lib
  ${shared_link_flags} )
