# Common sources
set(APP_SOURCES
    reader/FileReader.cpp
)

add_library(${APP_LIB_NAME} ${APP_SOURCES})

include_directories()
link_directories()

# Compile the application
option(COMPILE_APP "Compile the application" ON)
if(COMPILE_APP)
  add_executable(${APP_NAME} main.cpp)
  target_link_libraries(
      ${APP_NAME}
      ${APP_LIB_NAME}
      )
  install(TARGETS ${APP_NAME} DESTINATION bin/)
endif(COMPILE_APP)
