#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/utils/vec2image/source" path-vgen_vec2image-vgd )
file( GLOB_RECURSE files-vgen_vec2image-vgd "${path-vgen_vec2image-vgd}" "${path-vgen_vec2image-vgd}/*.cpp" )

add_library( vgen_vec2image-vgd SHARED ${files-vgen_vec2image-vgd} )

set_target_properties(      vgen_vec2image-vgd  PROPERTIES  OUTPUT_NAME "vut_vec2image" )
target_compile_definitions( vgen_vec2image-vgd  PUBLIC      ${shared_compile_def} )
target_compile_options(     vgen_vec2image-vgd  PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( vgen_vec2image-vgd   
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )
