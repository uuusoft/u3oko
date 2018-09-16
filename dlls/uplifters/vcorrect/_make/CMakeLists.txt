#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/uplifters/vcorrect" path-vcorrect_vdd )
file( GLOB_RECURSE files-vcorrect_vdd "${path-vcorrect_vdd}" "${path-vcorrect_vdd}/*.cpp" "${path-vcorrect_vdd}/*.hpp" )

add_library( vcorrect_vdd SHARED ${files-vcorrect_vdd} )

set_target_properties(      vcorrect_vdd    PROPERTIES  OUTPUT_NAME "vdd_vcorrect" )
target_compile_definitions( vcorrect_vdd    PUBLIC      ${shared_compile_def} )
target_compile_options(     vcorrect_vdd    PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vcorrect_vdd 
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
