#author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
#date       01.01.2017
#copyright  www.uuusoft.com
file( TO_CMAKE_PATH "${RELATIVE_PATH_TO_UUU_LIBS}/modules/uuu_appl" path-module-uuu_appl )
file( GLOB_RECURSE files-module-uuu_appl "${path-module-uuu_appl}" "${path-module-uuu_appl}/*.cpp" "${path-module-uuu_appl}/*.c" )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  add_library( module-uuu_appl SHARED ${files-module-uuu_appl} )
else()
  add_executable( module-uuu_appl ${files-module-uuu_appl} )
endif()

set_target_properties(      module-uuu_appl PROPERTIES  OUTPUT_NAME  "mpl_uuu_appl" )
target_compile_definitions( module-uuu_appl PUBLIC      ${shared_compile_def} )
target_compile_options(     module-uuu_appl PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)


if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )

  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_applications/framework )
  #include_directories(${PROJECT_SOURCE_DIR})
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vcos/pthreads )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vmcs_host/linux )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vmcs_host )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vmcs_host/khronos )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/khronos/include )
  #include_directories(${PROJECT_BINARY_DIR})
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vchiq_arm )
  #include_directories( tools/inet_transport )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_support/include )

  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_applications/linux/libs/bcm_host/include )
  #include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_applications/linux/apps/raspicam )
  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/host_applications/linux/libs/sm )

  include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland )
  #include_directories( ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/interface/vmcs_host/khronos )

  if ( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
    set( PATH_TO_RASPBERRY_LIBS ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/build/lib/release )
  else()
    set( PATH_TO_RASPBERRY_LIBS ${RELATIVE_PATH_TO_UUU_LIBS}/../sdks/userland/build/lib/debug )
  endif()

  find_library( vcos-lib NAMES vcos PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( bcm_host-lib NAMES bcm_host PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  #find_library( vchiq_arm-lib NAMES vchiq_arm PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  #find_library( EGL-lib NAMES EGL PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  #find_library( GLESv2-lib NAMES GLESv2 PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  #find_library( openmaxil-lib NAMES openmaxil PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  #find_library( mmal_omx-lib NAMES mmal_omx PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( mmal_util-lib NAMES mmal_util PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( mmal_core-lib NAMES mmal_core PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( mmal_vc_client-lib NAMES mmal_vc_client PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( vcsm-lib NAMES vcsm PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( bcm_host-lib NAMES bcm_host PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( vchiq_arm-lib NAMES vchiq_arm PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( brcmGLESv2-lib NAMES brcmGLESv2 PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )
  find_library( brcmEGL-lib NAMES brcmEGL PATHS ${PATH_TO_RASPBERRY_LIBS} NO_DEFAULT_PATH )

endif()

#set_target_properties(      module-uuu_appl PROPERTIES  OUTPUT_NAME  "mpl_uuu_appl" )
#target_compile_definitions( module-uuu_appl PUBLIC      ${shared_compile_def} )
#target_compile_options(     module-uuu_appl PUBLIC      ${shared_compile_options} $<$<COMPILE_LANGUAGE:CXX>:${shared_cpp_compile_options}>)
#target_link_libraries( module-uuu_appl  imdata_events-lib )
#target_link_libraries( module-uuu_appl  igui_events-lib )
#target_link_libraries( module-uuu_appl  ${shared_link_flags} )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Android" )
  target_link_libraries( module-uuu_appl  ${log-lib} )
endif()

target_link_libraries( module-uuu_appl
  ${all-boost-libs}
  ${all-generic-libs}
  ${all-igeneric-libs}
  ${all-event-libs}
  optim-lib
  ${shared_link_flags} )

if ( ${CMAKE_SYSTEM_NAME} STREQUAL "Raspberry" )

  target_link_libraries( module-uuu_appl
  ${vcos-lib}
  ${bcm_host-lib}
  ${mmal_util-lib}
  ${mmal_core-lib}
  ${mmal_vc_client-lib}
  ${vcsm-lib}
  ${bcm_host-lib}
  ${vchiq_arm-lib}
  ${brcmGLESv2-lib}
  ${brcmEGL-lib} )
  #${vchiq_arm-lib}
  #${EGL-lib}
  #${GLESv2-lib}
  #${openmaxil-lib}
  #${mmal_omx-lib}
  #${-lib}

endif()
