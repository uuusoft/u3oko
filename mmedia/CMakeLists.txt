# author      Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
# date        01.01.2017
# copyright   Erashov A.I.
# file        CMakeLists.txt

cmake_minimum_required(VERSION 3.29.0)

# check support applications
set(U3_INTERNAL_APPLS_LIST "u3oko")
if(U3_COMMERCIAL_PART EQUAL 1)
  set(U3_INTERNAL_APPLS_LIST ${U3_INTERNAL_APPLS_LIST} "u3okolite" "u3iplo" "u3cam")
endif()

if(NOT ${U3_APPL_NAME} IN_LIST U3_INTERNAL_APPLS_LIST)
  message(FATAL_ERROR "${U3_MARK_FATAL}Unknown application type U3_APPL_NAME=${U3_APPL_NAME} not in list U3_INTERNAL_APPLS_LIST=${U3_INTERNAL_APPLS_LIST}")
endif()

project(${U3_APPL_NAME} LANGUAGES C CXX ASM_NASM)

cmake_policy(SET CMP0057 NEW)

# generate compile_commands.json
# for sourcetrail https://github.com/coatisoftware/sourcetrail
# for clang-tidy sudo apt install clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(project_name ${U3_APPL_NAME})
# EAI-REFACT
set(project_version_major 0)
set(project_version_minor 2)

include(ExternalProject)
include(FetchContent)
include(FindWget)

include("./build/cmake/vals/env-mark-vals.cmake")
include("./build/cmake/vals/env-system-name-vals.cmake")

include("./build/cmake/funcs/u3-link-libs-to-target-func.cmake")
include("./build/cmake/funcs/u3-make-fake-file-func.cmake")
include("./build/cmake/funcs/u3-add-targert-dylib-func.cmake")
include("./build/cmake/funcs/u3-add-targert-lib-func.cmake")
include("./build/cmake/funcs/u3-url-validate-func.cmake")
include("./build/cmake/funcs/u3-project-add-func.cmake")
include("./build/cmake/funcs/u3-dump-vars-func.cmake")
include("./build/cmake/funcs/u3-get-major-version-func.cmake")

include("./build/cmake/vals/env-command-line-vals.cmake")
include("./build/cmake/vals/env-generate-vals.cmake")
include("./build/cmake/vals/env-internal-vals.cmake")

include("./build/cmake/utils/u3-folders.cmake")
include("./build/cmake/utils/u3-sanity-functional.cmake")
include("./build/cmake/utils/u3-check-preconditions.cmake")
include("./build/cmake/utils/u3-check-git.cmake")

include("./build/cmake/os-specific/u3-selector-os-specific-options.cmake")

if(U3_BUILD_MODULES_AS_LIBS)
  message(NOTICE "${U3_MARK_TODO}EAI-REFACT U3_BUILD_MODULES_AS_LIBS as DU3_BUILD_MODULES_AS_LIBS=1")
  set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} "-DU3_BUILD_MODULES_AS_LIBS=1")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/arc)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_SYSTEM_NAME}/${CMAKE_BUILD_TYPE})

include("./build/cmake/compiler-specific/u3-selector-compiler-specific-options.cmake")

set(U3_LINK_ALL_EVENTS_LIBS igui_events-lib imdata_events-lib istorage_events-lib ihttp_events-lib ievents_events-lib ilog_events-lib ievents-lib events-lib)
set(U3_LINK_ALL_GENERIC_LIBS properties-lib bufs-lib core-lib link-lib helpers-lib)
set(U3_LINK_ALL_IGENERIC_LIBS icore-lib ilink-lib iproperties-lib)

include("./build/cmake/utils/u3-update-config-project.cmake")
include("./build/cmake/module-specific/u3-define-modules.cmake")
include("./build/cmake/module-specific/u3-shared-3rd-libs-list.cmake")

include_directories("${U3_BUILD_PATH_TO_LIBS}/../")

# debug test compile
include("${U3_BUILD_PATH_TO_LIBS}/modules/mtest/_make/module-test.cmake")

# internal targets
include("${U3_BUILD_PATH_TO_LIBS}/libs/libs-list.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/utils/utils-list.cmake")
if(U3_COMMERCIAL_PART EQUAL 1)
  include("${U3_BUILD_PATH_TO_LIBS}/dshow_helpers/dshow-helpers-list.cmake")
endif()
include("${U3_BUILD_PATH_TO_LIBS}/dlls/dlls-list.cmake")

# lib-proxy depends from dlls
include("${U3_BUILD_PATH_TO_LIBS}/libs/proxy/_make/libs-proxy.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/appls/appls-list.cmake")
include("${U3_BUILD_PATH_TO_LIBS}/modules/modules-list.cmake")

if(U3_COMMERCIAL_PART EQUAL 1)
  include("./build/cmake/tests/u3-googletests.cmake")
endif()
