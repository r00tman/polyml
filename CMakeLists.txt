cmake_minimum_required (VERSION 2.6)
project (polyml)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(polyml STATIC pml_node.cpp)

install (TARGETS polyml DESTINATION lib)
install (FILES pml_node.h DESTINATION include)

enable_testing()
add_subdirectory(tests)

