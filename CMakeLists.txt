cmake_minimum_required(VERSION 3.5)
project(truth-tables VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(CTest)
enable_testing()

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/file_loader.cpp
    ${SOURCE_DIR}/logger.cpp
    ${SOURCE_DIR}/truth_table.cpp
)

set(HEADERS
    ${INCLUDE_DIR}/file_loader.hpp
    ${INCLUDE_DIR}/logger.hpp
    ${INCLUDE_DIR}/truth_table.hpp
)

add_executable(
    truth-tables 
    ${SOURCE_DIR}/main.cpp 
    ${SOURCES}
    ${HEADERS}
)
target_include_directories(truth-tables PRIVATE ${INCLUDE_DIR})
target_link_libraries(truth-tables PRIVATE stdc++fs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
