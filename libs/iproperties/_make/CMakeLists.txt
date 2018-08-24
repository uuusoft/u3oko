#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/libs/iproperties" path-lib )
file( GLOB_RECURSE files-lib "${path-lib}" "${path-lib}/*.cpp" "${path-lib}/*.hpp" )

add_library( iproperties-lib STATIC ${files-lib} )

target_compile_definitions( iproperties-lib    PUBLIC  ${shared_compile_def} )
target_compile_options(     iproperties-lib    PUBLIC  ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( iproperties-lib       
  ${all-boost-libs}
  core-lib
  icore-lib
  properties-lib
  helpers-lib
  ${shared_link_flags} )
