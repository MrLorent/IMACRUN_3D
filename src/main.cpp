#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "Program.hpp"
#include "FilePath.hpp"
#include "glm.hpp"
#include <vector>

struct Vertex{
    glm::vec3 position;
    glm::vec2 texture;
    glm::vec3 normal;

    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm)
        :position(pos), texture(tex), normal(norm)
    {

    }
};

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

    std::vector<Vertex> model;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {

                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                // access to vertex
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                glm::vec3 pos= glm::vec3(vx, vy, vz);

                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                glm::vec3 norm= glm::vec3(nx, ny, nz);

                tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
                glm::vec2 text= glm::vec2(tx,ty);

                Vertex shape = Vertex(pos, text, norm);
                model.push_back(shape);
            }
            index_offset += fv;
        }
    }

    //Initialisation des matrices
    glm::mat4 ProjMatrix=glm::perspective(glm::radians(70.f),float(window_width/window_height), 0.1f, 100.f);
    glm::mat4 id=glm::mat4(glm::vec4(1.0,0.,0.,0.), glm::vec4(0.,1.,0.,0.), glm::vec4(0.,0.,1.,0.), glm::vec4(0.,0.,0.,1.));
    glm::mat4 MVMatrix=glm::translate(id, glm::vec3(0.,0.,-10.));
    glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));

     // Creation du vbo
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

        glBufferData(
            GL_ARRAY_BUFFER,
            model.size()*sizeof(Vertex),
            model.data(),
            GL_STATIC_DRAW
        );

    glBindBuffer(GL_ARRAY_BUFFER,0);

    GLuint vao;
    const GLuint VERTEX_ATTR_POSITION = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            //POSITION
            glVertexAttribPointer(
                VERTEX_ATTR_POSITION,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, position))
            );

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
            glDrawArrays(
                GL_TRIANGLES,
                0,
                model.size()
            );
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}