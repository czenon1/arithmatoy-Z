cmake_minimum_required(VERSION 3.22)

project(arithmatoy)

add_library(
  arithmatoy
  src/arithmatoy.c
)
target_include_directories(
  arithmatoy
  PUBLIC src/include/
)
target_include_directories(
  arithmatoy
  PRIVATE src/
)
set_target_properties(
  arithmatoy
  PROPERTIES
  PUBLIC_HEADER src/include/arithmatoy.h
)

add_executable(
  arithmatoy-cli
  src/cli.c
)
target_include_directories(
  arithmatoy-cli
  PRIVATE src/include/ src/
)
target_link_libraries(arithmatoy-cli PRIVATE arithmatoy)

install(
  TARGETS arithmatoy arithmatoy-cli
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include
)

if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  enable_testing()
  find_package(cmocka CONFIG REQUIRED)

  foreach(test_file
    test_utils
    test_add
    test_sub
    test_mul
  )
    add_executable(${test_file} src/tests/${test_file}.c)
    target_link_libraries(${test_file} PRIVATE arithmatoy)
    target_include_directories(
      ${test_file}
      PRIVATE src/
    )
    target_link_libraries(${test_file} PRIVATE cmocka::cmocka)

    add_test(NAME ${test_file} COMMAND ${test_file})
  endforeach()
endif()
