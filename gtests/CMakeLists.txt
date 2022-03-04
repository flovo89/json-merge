set(
  TEST_APP_NAME 
  ${APP_NAME}_gtests
  )

file(
  GLOB_RECURSE 
  TEST_SOURCES 
  LIST_DIRECTORIES 
  false 
  *.hpp 
  *.cpp
  )

include_directories(
  ../src
  )

# link_directories()

set(
  SOURCES 
  ${TEST_SOURCES}
  )

add_executable(
  ${TEST_APP_NAME} 
  ${TEST_SOURCES}
  )

target_link_libraries(
  ${TEST_APP_NAME} 
  PUBLIC 
  ${APP_LIB_NAME}
  gmock
  gtest
  pthread
  )

# target_compile_options(
#   ${TEST_APP_NAME} 
#   PUBLIC 
#   )

# Execute the tests if necessary
option(RUN_GTESTS "Run the tests" ON)
if(RUN_GTESTS)
  add_custom_command(TARGET ${TEST_APP_NAME} 
  COMMAND 
  ./${TEST_APP_NAME} 
  POST_BUILD)
else()
  message(STATUS "Unit gtests won't be executed")
endif(RUN_GTESTS)