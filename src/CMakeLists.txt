project(static_source)

set(PROJECT_SOURCES GUI.cpp
                    graph.cpp)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../SFML/include
)


link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../SFML/build/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    sfml-graphics
    sfml-window
    sfml-system
    )
