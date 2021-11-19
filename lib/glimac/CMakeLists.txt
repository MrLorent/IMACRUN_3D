cmake_minimum_required(VERSION 3.10)

add_library(glimac)

file(GLOB_RECURSE GLIMAC_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(glimac PRIVATE ${GLIMAC_SOURCES})
target_include_directories(glimac PUBLIC ../glimac)

# ---Add GLFW---
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../glfw ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/build)
target_link_libraries(glimac PUBLIC glfw)

# ---Add glad---
add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/../glad/src/glad.c )
target_include_directories(glad PUBLIC ../glad/include)
target_link_libraries(glimac PUBLIC glad)

# ---Add glm---
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../glm ${CMAKE_CURRENT_SOURCE_DIR}/../glm/build)
target_link_libraries(glimac PUBLIC glm)

# FREETYPE
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../freetype-2.10.0 ${CMAKE_CURRENT_SOURCE_DIR}/../freetype-2.10.0/build)
target_link_libraries(glimac PUBLIC freetype
)

# ASSIMP
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../assimp-5.0.1 ${CMAKE_CURRENT_SOURCE_DIR}/../assimp-5.0.1/build)
target_link_libraries(glimac PUBLIC assimp)