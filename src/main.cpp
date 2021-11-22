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
#include <TrackballCamera.hpp>
#include <Image.hpp>
#include "Texture.hpp"

//Dimension de la fenêtre
GLFWwindow* window;
int window_width  = 720;
int window_height = 720;

//Creation de la camera
glimac::TrackballCamera cam= glimac::TrackballCamera();

glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;

struct Vertex{
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texCoords;

    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
        :_position(pos), _normal(norm), _texCoords(tex)
    {}
};

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

    /* Set the viewport */
    //glViewport(0, 0, window_width, window_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    return 1;
}

glimac::Program loadShader(glimac::FilePath applicationPath){
    glimac::Program program = loadProgram(
        applicationPath.dirPath() + "src/shaders/triangle.vs.glsl",
        applicationPath.dirPath() + "src/shaders/triangle.fs.glsl"
        );
    return program;
}

void loadTexture(glimac::FilePath applicationPath, GLuint &texture){
    std::unique_ptr<glimac::Image> image= glimac::loadImage(applicationPath.dirPath()+"assets/textures/alliance.png");
    if(image==nullptr){
        std::cout << "image non chargée " << std::endl;
    }
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
}

void loadMesh(std::vector<Vertex> &vec){
    //Chargement du model 3D
    std::string inputfile = "./assets/models/alliance.obj";
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
                Vertex newVertex = Vertex(
                    
                    // POSITION
                    glm::vec3(
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+0]), // vx
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+1]), // vy
                        tinyobj::real_t(attrib.vertices[3*idx.vertex_index+2])  // vz
                    ),

                    // NORMAL
                    glm::vec3(
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+0]),  // nx
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+1]),  // ny
                        tinyobj::real_t(attrib.normals[3*idx.normal_index+2])   // nz
                    ),

                    // TEXTURE_COORDINATES
                    glm::vec2(
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+0]),  //tx
                        tinyobj::real_t(attrib.texcoords[2*idx.texcoord_index+1])   //ty
                    )
                );

                vec.push_back(newVertex);
            }
            index_offset += fv;
        }
    }
}

void initMatrix(glm::mat4 &ProjMatrix, glm::mat4 &MVMatrix, glm::mat4 &NormalMatrix){
    //Initialisation des matrices
    ProjMatrix=glm::perspective(glm::radians(70.f),float(window_width/window_height), 0.1f, 100.f);
    glm::mat4 id=glm::mat4(1.);
    MVMatrix=glm::translate(id, glm::vec3(0.,0.,-10.));
    NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
}

void initVbo(GLuint &vbo, std::vector<Vertex> &model){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

        glBufferData(
            GL_ARRAY_BUFFER,
            model.size()*sizeof(Vertex),
            model.data(),
            GL_STATIC_DRAW
        );

    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void initVao(GLuint &vao, GLuint &vbo){
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            //POSITION
            glVertexAttribPointer(
                VERTEX_ATTR_POSITION,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, _position))
            );

                //NORMAL
            glVertexAttribPointer(
                VERTEX_ATTR_NORMAL,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, _normal))
            );

            //TEXTURE
            glVertexAttribPointer(
                VERTEX_ATTR_TEXTURE,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (const void*)(offsetof(Vertex, _texCoords))
            );

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void linkMatrix(GLint &uMVPMatrix, GLint &uMVMatrix, GLint &uNormalMatrix, GLint &uTexture, const glimac::Program &program){
    uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix"); 
    uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    uTexture = glGetUniformLocation(program.getGLId(), "uTexture");
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

    //Chargement des shaders
    glimac::FilePath applicationPath(argv[0]);
    glimac::Program program=loadShader(applicationPath);
    program.use();

    //Chargement de texture
    Texture textureChevalier(0);
    textureChevalier.load(applicationPath, "alliance.png");
    //loadTexture(applicationPath, textureChevalier);

    //Chargement de notre model 3D
    std::vector<Vertex> model;
    loadMesh(model);
    
    //Initialisation des matrices
    initMatrix(ProjMatrix, MVMatrix, NormalMatrix);
    
    //Initalisation du vbo
    GLuint vbo;
    initVbo(vbo, model);
     
    //Initialisation du vao
    GLuint vao;
    initVao(vao, vbo);

    //Liaison des matrices au shaders
    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;
    linkMatrix(uMVPMatrix, uMVMatrix, uNormalMatrix, uTexture, program);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindVertexArray(vao);
        MVMatrix= cam.getViewMatrix();

         //On charge la bonne texture
        glUniform1i(uTexture, 0);

        //Binding de la texture sur le 0
        textureChevalier.bind(0);

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix)); 

            glDrawArrays(
                GL_TRIANGLES,
                0,
                model.size()
            );

        //Debinding des textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,0); 
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}