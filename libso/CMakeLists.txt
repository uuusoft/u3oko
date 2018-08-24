#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
include( "${RELATIVE_PATH_TO_UUU_LIBS}/libso/libjpeg-turbo-master/_make/CMakeLists.txt" )
#include( "${RELATIVE_PATH_TO_UUU_LIBS}/libso/sqlite/_make/CMakeLists.txt" )
include( "${RELATIVE_PATH_TO_UUU_LIBS}/libso/dlib/_make/CMakeLists.txt" )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )
  #include( "${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vcos/CMakeLists.txt" )
  #include( "${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_applications/linux/CMakeLists.txt" )
  #include( "${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/CMakeLists.txt" )
endif()
