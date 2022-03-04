cmake_minimum_required (VERSION 3.2)
project (json-merge)

set(APP_NAME json-merge)
set(APP_LIB_NAME ${APP_NAME}_lib)

add_compile_options(-std=c++17 -Wall -Werror)

option(GENERATE_CODE_COVERAGE "Build the source with support for coverage analysis" OFF)
if(GENERATE_CODE_COVERAGE)
  message(STATUS "Building the source with support for coverage analysis")
  add_compile_options(-fprofile-arcs -ftest-coverage -O0)
  link_libraries(gcov)
endif()

# App version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_BUGFIX 0)
EXECUTE_PROCESS(COMMAND "date" "-u" "+%F %R" OUTPUT_VARIABLE COMPILE_DATE)
string(REGEX REPLACE "\n$" "" COMPILE_DATE "${COMPILE_DATE}")
EXECUTE_PROCESS(COMMAND
  "git" "describe" "--always" "--tags" "--dirty" "--abbrev=5"
  OUTPUT_VARIABLE GIT_HASH
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
string(REGEX REPLACE "\n$" "" GIT_HASH "${GIT_HASH}")
configure_file (
  "${PROJECT_SOURCE_DIR}/src/version.hpp.in"
  "${PROJECT_SOURCE_DIR}/src/version.hpp"
)

# Compile the app
add_subdirectory(src)

# Compile the unit tests
option(COMPILE_GTESTS "Compile the tests" ON)
if(COMPILE_GTESTS)
  add_subdirectory(gtests)
endif(COMPILE_GTESTS)
