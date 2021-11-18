cmake_minimum_required(VERSION 3.10)

# Set project name
project(IMACRUN_3D)

# Set C++ version
set(CXX_STANDARD 11)

# Set the path to the lib folder
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Set the path to the src folder
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the folder where the executable is created
set(EXECUTABLE_OUTPUT_PATH 
    ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
)

# GLFW
# Setting-up GLFW
set(GLFW_DIR ${LIB_DIR}/glfw)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)

# GLAD
set(GLAD_DIR ${LIB_DIR}/glad)
add_library(GLAD STATIC ${GLAD_DIR}/src/glad.c)

# FREETYPE
add_subdirectory(${LIB_DIR}/freetype-2.10.0)

# ASSIMP
add_subdirectory(${LIB_DIR}/assimp-5.0.1)

# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.hpp
)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

# create the executable file
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Include the directories containing our code
include_directories(
    lib
    lib/glimac
    include
    src
)

# OPENGL
find_package(OpenGL REQUIRED)
# Include the directories containing OpenGL's code
include_directories(
    ${OPENGL_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARIES}
    freetype
    assimp
)

# GLAD
target_include_directories(GLAD PRIVATE ${GLAD_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_DIR}/include)
target_link_libraries(${PROJECT_NAME}
    GLAD
)

#GLFW
# Including GLFW into IMACRUN_3D code space
include_directories(
    ${GLFW_DIR}/include
    ${GLFW_DIR}/deps
)
target_link_libraries(${PROJECT_NAME}
    glfw
)

# Including GLM into IMACRUN_3D code space
set(GLM_DIR ${LIB_DIR}/glm)
include_directories(
    ${GLM_DIR}
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