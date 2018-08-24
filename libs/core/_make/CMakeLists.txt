#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/core" path-lib )
file( GLOB_RECURSE files-lib "${path-lib}" "${path-lib}/*.cpp" )

add_library( core-lib STATIC ${files-lib} )

target_compile_definitions( core-lib    PUBLIC  ${shared_compile_def} )
target_compile_options(     core-lib    PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( core-lib       
  ${all-boost-libs}
  helpers-lib
  ${shared_link_flags} )
