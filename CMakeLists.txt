cmake_minimum_required (VERSION 2.6)

project (QTREE_SFML)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
if (APPLE)
   set (CMAKE_MODULE_PATH "/usr/local/share/SFML/cmake/Modules/")
endif (APPLE)

set (CMAKE_INCLUDE_PATH inc)
set (CMAKE_CXX_COMPILER clang++)
#set (CMAKE_CXX_FLAGS "-g3 -Wall -pedantic")

set (SOURCES
  main.cpp
  Core.cpp
  Circle.cpp
  Quadtree.cpp
  Object.cpp

  )

set(EXECUTABLE_NAME a.out)
add_executable (${EXECUTABLE_NAME} ${SOURCES})

find_package(SFML 2 REQUIRED system window graphics)

if(SFML_FOUND)
  include_directories(inc ${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
