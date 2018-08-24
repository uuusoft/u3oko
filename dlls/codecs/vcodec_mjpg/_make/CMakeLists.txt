#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/vcodec_mjpg" path-vcodec_vvd )
file( GLOB_RECURSE files-vcodec_vvd "${path-vcodec_vvd}" "${path-vcodec_vvd}/*.cpp" )

add_library( vcodec_mjpg_vvd SHARED ${files-vcodec_vvd} )

set_target_properties(      vcodec_mjpg_vvd PROPERTIES  OUTPUT_NAME "vvd_vcodec_mjpg" )
target_compile_definitions( vcodec_mjpg_vvd PUBLIC      ${shared_compile_def} )
target_compile_options(     vcodec_mjpg_vvd PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vcodec_mjpg_vvd
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  optim_s16bit_generic-lib
  optim_freq-lib
  codec_gen-lib
  codec_functs-lib
  turbo_jpeg-lib
  ${shared_link_flags} )
