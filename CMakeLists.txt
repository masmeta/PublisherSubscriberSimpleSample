CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(subpubSample)

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
