#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "Program.hpp"
#include "FilePath.hpp"
#include "glm.hpp"

int window_width  = 1280;
int window_height = 720;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    window_width  = width;
    window_height = height;
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a window and its OpenGL context */
#ifdef __APPLE__
    /* We need to explicitly ask for a 3.3 context on Mac */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "IMACRUN_3D", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    //Chargement des shaders
    glimac::FilePath applicationPath(argv[0]);
    glimac::Program program = loadProgram(
        applicationPath.dirPath() + "src/shaders/triangle.vs.glsl",
        applicationPath.dirPath() + "src/shaders/triangle.fs.glsl"
        );
    program.use();

    //Chargement du model 3D
    std::string inputfile = "./assets/models/cup.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib,&shapes,&materials, &warn, &err, inputfile.c_str(), nullptr);
    
    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }


    //Initialisation des matrices
    glm::mat4 ProjMatrix=glm::perspective(glm::radians(70.f),float(window_width/window_height), 0.1f, 100.f);
    glm::mat4 id=glm::mat4(glm::vec4(1.0,0.,0.,0.), glm::vec4(0.,1.,0.,0.), glm::vec4(0.,0.,1.,0.), glm::vec4(0.,0.,0.,1.));
    glm::mat4 MVMatrix=glm::translate(id, glm::vec3(0.,0.,-5.));
    glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));

     // Creation du vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    glBufferData(
        GL_ARRAY_BUFFER,
        attrib.vertices.size()*sizeof(GLfloat),
        attrib.vertices.data(),
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ARRAY_BUFFER,0);

    const GLuint VERTEX_ATTR_POSITION = 0;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //POSITION
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(tinyobj::attrib_t), (const void*)(offsetof(tinyobj::attrib_t, vertices)));

     glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);





    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, attrib.vertices.size());
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}