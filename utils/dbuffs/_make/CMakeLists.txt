#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/utils/dbuffs" path-dll-dbuffs )
file( GLOB_RECURSE files-dll-dbuffs "${path-dll-dbuffs}" "${path-dll-dbuffs}/*.cpp" "${path-dll-dbuffs}/*.hpp" )

include_directories( "../../../../../boost/" )

add_library( dbuffs-dll SHARED ${files-dll-dbuffs} )

set_target_properties(      dbuffs-dll   PROPERTIES  OUTPUT_NAME "dbuffs" )
target_compile_definitions( dbuffs-dll   PUBLIC      		 ${shared_compile_def} )
target_compile_options(     dbuffs-dll   PUBLIC      		 ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)

target_link_libraries( dbuffs-dll    
  ${all-boost-libs}
  ${log-lib}
  ${all-generic-libs}
  ${all-igeneric-libs}
  events-lib
  ${shared_link_flags} )
