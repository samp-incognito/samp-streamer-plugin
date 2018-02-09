cmake_minimum_required(VERSION 3.0)
project(streamer)

set(PLUGIN_VERSION "2.9.3")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/lib/cmake-modules")

set(SAMP_SDK_ROOT "${PROJECT_SOURCE_DIR}/lib/samp-plugin-sdk")
find_package(SAMPSDK REQUIRED)
include_directories(${SAMPSDK_DIR})
include_directories(${SAMPSDK_DIR}/amx)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.63.0 REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Eigen3 3.3.4 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY True)
set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY True)

add_subdirectory(src)

set(CPACK_PACKAGE_VERSION ${PLUGIN_VERSION})

if(WIN32)
	set(CPACK_GENERATOR ZIP)
else()
	set(CPACK_GENERATOR TGZ)
endif()

include(CPack)
