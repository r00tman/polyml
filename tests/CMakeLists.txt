enable_testing()

include_directories(. ../)

add_executable(basic_io_test basic_io_test.cpp)
target_link_libraries(basic_io_test polyml)

add_executable(speed_test speed_test.cpp)
target_link_libraries(speed_test polyml)

add_test(basic_io_test ${CMAKE_CURRENT_BINARY_DIR}/basic_io_test)
add_test(speed_test ${CMAKE_CURRENT_BINARY_DIR}/speed_test)