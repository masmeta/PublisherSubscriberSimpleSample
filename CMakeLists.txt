CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(subpubSample)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif( NOT CMAKE_BUILD_TYPE)

message(STATUS "CMAKE_BUILD_TYPE set by user to ${CMAKE_BUILD_TYPE}.")
message(STATUS " |- CMAKE_BUILD_TYPE not set by user setting it to ${CMAKE_BUILD_TYPE} by default.")
message(STATUS " |- If you want to build Debug version please set CMAKE_BUILD_TYPE to Debug in the cmake COMMAND line with -DCMAKE_BUILD_TYPE=Debug")

# Get version from git
find_package(Git)
if(GIT_FOUND)
  EXECUTE_PROCESS(
    COMMAND git describe --long
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE "CURRENT_BUILD_VERSION"
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "Git describe returned: ${CURRENT_BUILD_VERSION}")
  set(VERSION_PATCH ${CURRENT_BUILD_VERSION})
  string(REGEX MATCH "v([0-9]+)\\.([0-9]+)\\-(.*)" version_valid ${CURRENT_BUILD_VERSION})
  if(version_valid)
    string(REGEX REPLACE "v([0-9]+)\\.([0-9]+)\\-(.*)" "\\1;\\2;\\3" VERSION_MATCHES ${CURRENT_BUILD_VERSION})
    list(GET VERSION_MATCHES 0 version_major)
    set(VERSION_MAJOR ${version_major})

    list(GET VERSION_MATCHES 1 version_minor)
    set(VERSION_MINOR ${version_minor})

    list(GET VERSION_MATCHES 2 version_patch)
    set(VERSION_PATCH ${version_patch})
  else()
    message(FATAL_ERROR "*META* Problem to get git based version from regex")
  endif()
else()
    message(FATAL_ERROR "*META* Problem to get git based version")
endif()

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(VERSION_NOHASH "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message(STATUS "Building project version ${VERSION}")
configure_file (
    "${CMAKE_SOURCE_DIR}/version.in"
    "${CMAKE_CURRENT_LIST_DIR}/src/include/version.h"
    @ONLY
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -O3 ")
    ADD_DEFINITIONS(-fpermissive)
	ADD_DEFINITIONS(-Dnullptr=0) # needed for some compilers
ENDIF()

FILE(GLOB_RECURSE SRC "${CMAKE_CURRENT_LIST_DIR}/src/src/*.cpp")

#Create executable
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/include/") 
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp" ${SRC})
target_link_libraries(${PROJECT_NAME} )
