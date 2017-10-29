###########################
# CMake Build Environment #
###########################
#
# You can set the following Environment variables:
#
# CMAKE_MODULE_PATH to the search path for cmake modules (e.g., SFML.cmake)
# CMAKE_BUILD_TYPE to override the default build type. Valid options are 'release', 'profile' and 'debug'
#
#########################################

# Project name
project(game)

# Minimum Cmake Version
cmake_minimum_required(VERSION 2.6)

#####################
# Setup Environment #
#####################
# set to include custom modules
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} ${game_SOURCE_DIR}/cmake)

# set build type if specified by environment
if((NOT CMAKE_BUILD_TYPE) AND (NOT $ENV{CMAKE_BUILD_TYPE} STREQUAL ""))
    set(CMAKE_BUILD_TYPE $ENV{CMAKE_BUILD_TYPE})
endif()

# Set include directories
include_directories(${game_SOURCE_DIR}/include)

# Get CPP files
file(GLOB_RECURSE SRC src/*cpp)

# Get Header files
file(GLOB_RECURSE HEADERS include/*h)

# Get executable files
file(GLOB EXECLIST bin/*cpp)

# Get media files
file(COPY media DESTINATION .)


#################################################
#                                               #
# ADD CUSTOM LIBRARIES HERE.                    #
#                                               #
# Example BOOST:                                #
#  find_package(Boost REQUIRED)                 #
#  include_directories(${Boost_INCLUDE_DIRS})   #
#  link_libraries(${Boost_LIBRARIES})           #
#################################################

##################
# Add Chipmunk2D #
##################
option(BUILD_DEMOS OFF)
add_subdirectory(lib/Chipmunk2D)
include_directories(lib/Chipmunk2D/include/chipmunk)
link_libraries(chipmunk)

#############
# Add gason #
#############
add_subdirectory(lib/gason)
set_target_properties(test-suite gasonpp benchmark PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
if(MSVC)
  get_target_property(FLAGS gason COMPILE_OPTIONS)
  list(REMOVE_ITEM FLAGS -Wall -Wextra)
  set_property(TARGET gason PROPERTY COMPILE_OPTIONS ${FLAGS})
endif()
get_target_property(FLAGS gason COMPILE_OPTIONS)
include_directories(lib/gason/src)
link_libraries(gason)

#############
# json11 #
#############
add_subdirectory(lib/json11)
include_directories(lib/json11)
link_libraries(json11)

#############
# Find SFML #
#############
find_package(SFML COMPONENTS graphics window system audio network)
include_directories(${SFML_INCLUDE_DIR})
link_libraries(${SFML_LIBRARIES})

if(NOT SFML_FOUND)
  # SFML not found
  message(FATAL_ERROR " * Make sure LIB includes the directory where the SFML libraries are installed.\n * Make sure INCLUDE includes the directory where the SFML header files are installed.")	
endif()

###############
# C++ Options #
###############
# Enable C++11
# Change compiler flag for MSVC, do not check other compiler type.
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

# determine build type
# 1) use build type if specified by the user.
# 2) if in-source building, use default (debug) build type.
# 3) if out-source building, determine based on the build directory's name which build type. 
#    If build directory is called 'Release' or 'Profile' then use the 'Release' and 'Profile' 
#    build type respectively, otherwise use 'debug'.
if(CMAKE_BUILD_TYPE)
  string(TOUPPER "${CMAKE_BUILD_TYPE}" TYPE)
  message("-- Using user specified build type: ${TYPE}")
elseif(${game_SOURCE_DIR} STREQUAL ${game_BINARY_DIR})
  set(CMAKE_BUILD_TYPE Debug)
  message("-- In-source building. Build type set to: Debug")
else()
  get_filename_component(TYPE ${game_BINARY_DIR} NAME)
  string(TOUPPER "${TYPE}" TYPE)
  if(${TYPE} STREQUAL "RELEASE")
    set(CMAKE_BUILD_TYPE Release)
  elseif(${TYPE} STREQUAL "PROFILE")
    set(CMAKE_BUILD_TYPE Profile)
  else()
    set(CMAKE_BUILD_TYPE Debug)
 endif()
 message("-- Out-source building. Build type set to: ${TYPE}")
endif()

# Handle non-default build type 'Profile'
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)
if(${CMAKE_BUILD_TYPE} STREQUAL "PROFILE")
  set(CMAKE_BUILD_TYPE DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()

#######################
# Set Compile Targets #
#######################
# src library (all CPP files in 'src' dir)
if(NOT SRC STREQUAL "")
  get_filename_component(LIBNAME ${game_SOURCE_DIR} NAME)
  set(LIBNAME "${LIBNAME}_core")
  add_library(${LIBNAME} ${SRC})
endif()

# executables (any CPP file in 'bin' dir)
foreach(EXEC ${EXECLIST})
  get_filename_component(EXECNAME ${EXEC} NAME_WE)
  add_executable(${EXECNAME} ${EXEC} ${SRC} ${HEADERS})

  if(NOT SRC STREQUAL "")
    target_link_libraries(${EXECNAME} LINK_PUBLIC ${LIBNAME})
  endif()

  message("-- Adding executable: ${EXECNAME}")
endforeach(EXEC)

