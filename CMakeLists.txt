cmake_minimum_required(VERSION 3.10)

# Set project name
project(IMACRUN_3D)

# Set C++ version
set(CXX_STANDARD 14)

# Set the path to the lib folder
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
# Set the path to the src folder
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the folder where the executable is created
set(EXECUTABLE_OUTPUT_PATH 
    ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/glimac/*.hpp
    ${CMAKE_SOURCE_DIR}/src/rendering/*.hpp
)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/glimac/*.cpp
    ${CMAKE_SOURCE_DIR}/src/rendering/*.cpp
)

# create the executable file
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Include the directories containing our code
include_directories(
    src
    src/glimac
    src/rendering
)

# ---Add GLFW---
add_subdirectory(${LIB_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# ---Add glad---
add_library(glad ${LIB_DIR}/glad/src/glad.c)
target_include_directories(glad PUBLIC ${LIB_DIR}/glad/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

# ---Add glm---
add_subdirectory(${LIB_DIR}/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

# ---Add FreeType---
add_subdirectory(${LIB_DIR}/freetype)
target_link_libraries(${PROJECT_NAME} PUBLIC freetype)

# ---Add tinyobjloader---
add_subdirectory(${LIB_DIR}/tinyobjloader)
target_link_libraries(${PROJECT_NAME} PUBLIC tinyobjloader)

# ---Add header librairies---
include_directories(
    ${LIB_DIR}/stb
    ${LIB_DIR}/dirent
)

#
#Add a post build operation to copy shaders to the output folder (where the executable is created)
#
function(copy_folder_to_the_output_folder _FOLDERPATH)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${_FOLDERPATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/${_FOLDERPATH}
)
endfunction()
copy_folder_to_the_output_folder("assets")
copy_folder_to_the_output_folder("src/shaders")