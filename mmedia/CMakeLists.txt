# author      Erashov Anton erashov2026@proton.me
# date        01.01.2017
# copyright   Erashov A.I.
# file        CMakeLists.txt

cmake_minimum_required(VERSION 3.29.0)
project(${U3_APPL_NAME} LANGUAGES C CXX ASM_NASM)
# https://cmake.org/cmake/help/latest/manual/cmake-policies.7.html
cmake_policy(SET CMP0057 NEW) # Support new if() IN_LIST operator
cmake_policy(SET CMP0167 OLD) # The FindBoost module is removed

# for sourcetrail https://github.com/coatisoftware/sourcetrail
# for clang-tidy sudo apt install clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate compile_commands.json

set(project_name ${U3_APPL_NAME})

# EAI-REFACT
set(project_version_major 0)
set(project_version_minor 3)

include(ExternalProject)
include(FetchContent)
include(FindWget)

# external variables
include("./.ci/cmake/vals/env-mark-vals.cmake")
include("./.ci/cmake/vals/env-system-name-vals.cmake")
# functions
include("./.ci/cmake/funcs/u3-link-libs-to-target-func.cmake")
include("./.ci/cmake/funcs/u3-make-fake-file-func.cmake")
include("./.ci/cmake/funcs/u3-add-targert-dylib-func.cmake")
include("./.ci/cmake/funcs/u3-add-targert-lib-func.cmake")
include("./.ci/cmake/funcs/u3-url-validate-func.cmake")
include("./.ci/cmake/funcs/u3-project-add-func.cmake")
include("./.ci/cmake/funcs/u3-dump-vars-func.cmake")
include("./.ci/cmake/funcs/u3-get-major-version-func.cmake")
include("./.ci/cmake/funcs/u3-is-target-os-linux-func.cmake")
include("./.ci/cmake/funcs/u3-dump-vars-func.cmake")
# internal variables
include("./.ci/cmake/vals/env-command-line-vals.cmake")
include("./.ci/cmake/vals/env-generate-vals.cmake")
include("./.ci/cmake/vals/env-internal-vals.cmake")
# after generate env variable
include_directories("${U3_PATH_ROOT}/../")

# checks preconditions
include("./.ci/cmake/utils/u3-setup-sanity.cmake")
include("./.ci/cmake/utils/u3-check-preconditions.cmake")
include("./.ci/cmake/utils/u3-check-git.cmake")

include("./.ci/cmake/specific-os/u3-selector-os-specific-options.cmake")

if (U3_BUILD_AS_MONOLITH)
  message(NOTICE "${U3_MARK_TODO}EAI-REFACT U3_BUILD_AS_MONOLITH as DU3_BUILD_AS_MONOLITH=1")
  set(U3_SHARED_COMPILE_DEF_CPP ${U3_SHARED_COMPILE_DEF_CPP} "-DU3_BUILD_AS_MONOLITH=1")
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_PLATFORM_NAME}/${CMAKE_BUILD_TYPE}/arc)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_PLATFORM_NAME}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${U3_PLATFORM_NAME}/${CMAKE_BUILD_TYPE})

include("./.ci/cmake/specific-compiler/u3-selector-compiler-specific-options.cmake")
include("./.ci/cmake/utils/u3-update-config-project.cmake")
include("./.ci/cmake/specific-module/u3-define-modules.cmake")
# external targets
include("./.ci/cmake/specific-module/u3-shared-3rd-libs-list.cmake")
# internal libs targets, depends from external targets
include("./libs/libs-list.cmake")
include("./utils/utils-list.cmake")
# for debug test compile
include("./modules/mtest/-module-test.cmake")

# EAI-REFACT move to dnodes
if (U3_COMMERCIAL_PART EQUAL 1)
  include("./utils/dshow_helpers/dshow-helpers-list.cmake")
endif ()

# internal dnodes targets, depends from internal libs
include("./dnodes/dnodes-list.cmake")
# lib-proxy depends from internal dnodes
include("./libs/proxy/libs-proxy.cmake")
# list applicaions
include("./appls/appls-list.cmake")
# list modules, depends from applications
include("./modules/-modules-list.cmake")
# test
if (U3_COMMERCIAL_PART EQUAL 1)
  include("./.ci/cmake/tests/u3-googletests.cmake")
endif ()

u3_dump_vars()
