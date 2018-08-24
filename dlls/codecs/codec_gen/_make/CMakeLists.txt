#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/dlls/codecs/codec_gen" path-codec_gen-lib )
file( GLOB_RECURSE files-codec_gen-lib "${path-codec_gen-lib}" "${path-codec_gen-lib}/*.cpp" )

add_library( codec_gen-lib STATIC ${files-codec_gen-lib} )

target_compile_definitions( codec_gen-lib   PUBLIC  ${shared_compile_def} )
target_compile_options(     codec_gen-lib   PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( codec_gen-lib
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${shared_link_flags} )
