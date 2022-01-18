cmake_minimum_required(VERSION 3.20)
project("data-structures" VERSION 0.0.1.0)

set(SRC "linked-list.cpp")

add_executable(main "${SRC}")

set_target_properties(
  main
  PROPERTIES
  CXX_STANDARD_REQUIRED 98
)
