CMAKE_MINIMUM_REQUIRED( VERSION 2.8.7 )
PROJECT( Pump CXX )

IF( CMAKE_MAJOR_VERSION GREATER 3 OR ( CMAKE_MAJOR_VERSION EQUAL 3 AND CMAKE_MINOR_VERSION GREATER 0 ) )
  SET( CMAKE_CXX_STANDARD 11 )
  SET( CMAKE_CXX_STANDARD_REQUIRED ON )
ELSE()
  # This is not the nicest way of activating C++11, but it is guaranteed to
  # work with older versions
  ADD_DEFINITIONS( "-std=c++11" ) 
ENDIF()

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

INCLUDE( CheckCXXCompilerFlag )

FILE( GLOB filenames "cmake/Macros/*.cmake" )
FOREACH( filename ${filenames} )
  INCLUDE( ${filename} )
ENDFOREACH()

ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wall" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wconversion" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wextra" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wnon-virtual-dtor" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wold-style-cast" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Woverloaded-virtual" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wself-init" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-Wunsafe-loop-optimization" )
ENABLE_IF_SUPPORTED( CMAKE_CXX_FLAGS "-pedantic" )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} )

#
# Executables
#

ADD_EXECUTABLE( harness
  Harness.cc
  Processes.cc
)

ADD_EXECUTABLE( pump
  Edge.cc
  Filesystem.cc
  Node.cc
  Processes.cc
  Pump.cc
)

#
# Subdirectories
#

ADD_SUBDIRECTORY( examples )

#
# Place compile commands in the source directory
#

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()
