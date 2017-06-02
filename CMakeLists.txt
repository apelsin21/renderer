cmake_minimum_required(VERSION 2.6)
project(renderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
endif()

find_path(FREETYPE_INCLUDE_DIRS freetype/freetype.h HINTS /usr/include/freetype2)
include(FindPkgConfig)
include(FindPackageHandleStandardArgs)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(EPOXY REQUIRED epoxy)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
  ${OPENGL_INCLUDE_DIR}
  ${FREETYPE_INCLUDE_DIRS}
  ${EPOXY_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(
  ${PROJECT_NAME}
  SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${SOURCES}
  ${HEADERS}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${EPOXY_LIBRARIES}
  ${OPENGL_LIBRARY}
  ${FREETYPE_LIBRARIES}
  ${FREEIMAGE_LIBRARIES}
  freeimage
  ${SDL2_LIBRARIES}
)

project(testrunner)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/unittests)

add_executable(
  ${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/unittests/main.cpp
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)

target_link_libraries(
  ${PROJECT_NAME}
  renderer
)
