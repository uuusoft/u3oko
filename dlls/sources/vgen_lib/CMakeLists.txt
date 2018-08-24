#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/sources/vgen_lib/source" path-gen_lib-lib )
file( GLOB_RECURSE files-gen_lib-lib "${path-gen_lib-lib}" "${path-gen_lib-lib}/*.cpp" )

add_library( gen_lib-lib STATIC ${files-gen_lib-lib} )

target_compile_definitions( gen_lib-lib PUBLIC  ${shared_compile_def} )
target_compile_options(     gen_lib-lib PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( gen_lib-lib      
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  events-lib
  ievents-lib
  ${shared_link_flags} )
