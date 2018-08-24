#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_gen/source" path-vcodec_gen-vdd )
file( GLOB_RECURSE files-vcodec_gen-vdd "${path-vcodec_gen-vdd}" "${path-vcodec_gen-vdd}/*.cpp" )

add_library( vcodec_gen-vdd SHARED ${files-vcodec_gen-vdd} )

set_target_properties(      vcodec_gen-vdd  PROPERTIES  OUTPUT_NAME "vdd_vcodec_gen" )
target_compile_definitions( vcodec_gen-vdd  PUBLIC      ${shared_compile_def} )
target_compile_options(     vcodec_gen-vdd  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vcodec_gen-vdd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  codec_gen-lib
  codec_functs-lib
  ${shared_link_flags} )
