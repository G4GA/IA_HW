cmake_minimum_required(VERSION 3.27)

project(IA)
set(CMAKE_BUILD_TYPE Debug)

# Add compiler flags for debugging (optional, depending on your compiler)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-g -O0 -Wall -Wextra -Wpedantic)
endif()

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/SFML)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE static_source)
