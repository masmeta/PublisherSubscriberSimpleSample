CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(subpubSample)
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
endIF( NOT CMAKE_BUILD_TYPE)

message(STATUS "CMAKE_BUILD_TYPE SET by user to ${CMAKE_BUILD_TYPE}.")
message(STATUS " |- CMAKE_BUILD_TYPE not SET by user SETting it to ${CMAKE_BUILD_TYPE} by default.")
message(STATUS " |- IF you want to build Debug version please SET CMAKE_BUILD_TYPE to Debug in the cmake COMMAND line with -DCMAKE_BUILD_TYPE=Debug")


IF (BUILD_DOC)
  # check if Doxygen is installed
  find_package(Doxygen REQUIRED)
  if (DOXYGEN_FOUND)
      # set input and output files
      set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/documentations/Doxyfile.in)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

      # request to configure the file
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      message(STATUS "Doxygen build started")

      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating API documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message(STATUS "Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
ENDIF(BUILD_DOC)

# Get version from git
find_package(Git)
IF(GIT_FOUND)
  EXECUTE_PROCESS(
    COMMAND git describe --long
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    OUTPUT_VARIABLE "CURRENT_BUILD_VERSION"
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message(STATUS "Git describe returned: ${CURRENT_BUILD_VERSION}")
  SET(VERSION_PATCH ${CURRENT_BUILD_VERSION})
  string(REGEX MATCH "v([0-9]+)\\.([0-9]+)\\-(.*)" version_valid ${CURRENT_BUILD_VERSION})
  IF(version_valid)
    string(REGEX REPLACE "v([0-9]+)\\.([0-9]+)\\-(.*)" "\\1;\\2;\\3" VERSION_MATCHES ${CURRENT_BUILD_VERSION})
    list(GET VERSION_MATCHES 0 version_major)
    SET(VERSION_MAJOR ${version_major})

    list(GET VERSION_MATCHES 1 version_minor)
    SET(VERSION_MINOR ${version_minor})

    list(GET VERSION_MATCHES 2 version_patch)
    SET(VERSION_PATCH ${version_patch})
  ELSE()
    message(FATAL_ERROR "*META* Problem to get git based version from regex")
  endIF()
ELSE()
    message(FATAL_ERROR "*META* Problem to get git based version")
endIF()

SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
SET(VERSION_NOHASH "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message(STATUS "Building project version ${VERSION}")
configure_file (
    "${CMAKE_SOURCE_DIR}/version.in"
    "${CMAKE_CURRENT_LIST_DIR}/src/include/version.h"
    @ONLY
)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -O3 ")
    ADD_DEFINITIONS(-fpermissive)
  ADD_DEFINITIONS(-Dnullptr=0) # needed for some compilers
ELSEIF(MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp /fp:fast")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /GL /O2 /Ob2 /Ot /DNDEBUG")
ENDIF()

IF(CMAKE_SYSTEM_NAME MATCHES Windows)
    IF(${ARCH_SIZE} MATCHES 32)
        SET(ARCH x86)
    ELSEIF(${ARCH_SIZE} MATCHES 64)
        SET(ARCH x64)
    ELSE()
        SET(ARCH Win)
    endIF()

    IF(MSVC)
        IF(MSVC10)
            SET(VC_VERS "_vc10")
        ELSEIF(MSVC11)
            SET(VC_VERS "_vc11")
        ELSEIF(MSVC12)
            SET(VC_VERS "_vc12")
        ELSEIF(MSVC14)
            SET(VC_VERS "_vc14")
        ELSEIF(MSVC15)
            SET(VC_VERS "_vc15")
        endIF()
    ELSE()
        SET(VC_VERS "")
    endIF()
ENDIF()

FILE(GLOB_RECURSE SRC "${CMAKE_CURRENT_LIST_DIR}/src/src/*.cpp")

#Create executable
include_directories("${CMAKE_CURRENT_LIST_DIR}/src/include/") 
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp" ${SRC})
target_link_libraries(${PROJECT_NAME} )
