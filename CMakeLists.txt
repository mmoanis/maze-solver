CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(MazeSolver)
###########################################################
#### Build checks
# Stop build if src dir is the same as build dir
IF(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
	MESSAGE(FATAL_ERROR "Please select another build directory other than the source directory")
ENDIF()

# Warn for spaces in directories
IF(CMAKE_SOURCE_DIR MATCHES " ")
	MESSAGE("Source directory contains spaces. This can lead to compilation problems.")
ENDIF()
IF(CMAKE_BINARY_DIR MATCHES " ")
	MESSAGE("Build directory contains spaces. This can lead to compilation problems.")
ENDIF()
# -D CMAKE_BUILD_TYPE=Release/Debug
IF(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF()

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc")
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


# SRC
SET(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES("${INCLUDE_DIR}")
SET(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
AUX_SOURCE_DIRECTORY(${SRC_DIR} SRC_FILES)

SET (ENV{SFML_ROOT} "${CMAKE_SOURCE_DIR}/external/SFML/")
FIND_PACKAGE(SFML REQUIRED system window graphics network audio)
IF (SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    LINK_LIBRARIES(${SFML_LIBRARIES})
ENDIF()


ADD_EXECUTABLE(MazeSolver "${SRC_FILES}")

SET_TARGET_PROPERTIES(MazeSolver PROPERTIES POSITION_INDEPENDENT_CODE ON)
