#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
// #define TINYOBJLOADER_IMPLEMENTATION
// #include <tiny_obj_loader.h>
#include "Program.hpp"
#include "FilePath.hpp"
#include "glm.hpp"
#include <vector>
#include <TrackballCamera.hpp>
#include <Image.hpp>
#include "Texture.hpp"
#include "Model.hpp"

//Dimension de la fenêtre
GLFWwindow* window;
int window_width  = 720;
int window_height = 720;

//Creation de la camera
glimac::TrackballCamera cam= glimac::TrackballCamera();

glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

int init(const int &window_width, const int &window_height){

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
    
    window = glfwCreateWindow(
        window_width,
        window_height,
        "IMACRUN_3D",
        nullptr,
        nullptr
    );

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Intialize glad (loads the OpenGL functions) */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Set the OpenGL environnement */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    return 1;
}

void initMatrix(glm::mat4 &ProjMatrix, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix){
    //Initialisation des matrices
    ProjMatrix=glm::perspective(glm::radians(70.f),float(window_width/window_height), 0.1f, 100.f);
    glm::mat4 id=glm::mat4(1.);
    MVMatrix=glm::translate(id, glm::vec3(0.,0.,-10.));
    NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
        switch (key)
        {
        case 262: //Fleche droite
            if(action!=0){
                cam.rotateSide(-2.*float(1));
            }
            break;

        case 263: //Fleche gauche
            if(action!=0){
                cam.rotateSide(2.*float(1));
            }
            break;

        case 264: //Fleche bas
            if(action!=0){
                cam.rotateUp(-2.*float(1));
            }
            break;
        
        case 265: //Fleche haut
            if(action!=0){
                cam.rotateUp(2.*float(1));
            }
            break;

        default:
            break;
        }
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.moveFront(yoffset);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

static void size_callback(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    ProjMatrix = glm::perspectiveFov(
        glm::radians(70.0f),
        float(width),
        float(height),
        0.1f,
        100.0f
    );
}

int main(int argc, char** argv)
{
    //Creation de la fenêtre
    init(window_width, window_height);

    /* Hook input callbacks */
    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetWindowSizeCallback(window, &size_callback);

    ModelParams knitParams(
        glimac::FilePath(argv[0]),
        "alliance.obj",
        "triangle.vs.glsl",
        "triangle.fs.glsl"
    );
    Model chevalier(knitParams);
    
    //Initialisation des matrices
    initMatrix(ProjMatrix, MVMatrix, NormalMatrix);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        MVMatrix= cam.getViewMatrix(); 
        glUniform1i(chevalier._uTexture, 0);
        texChevalier.bind(0);
        chevalier.draw(ProjMatrix, MVMatrix, NormalMatrix);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}