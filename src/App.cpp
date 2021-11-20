#include "App.hpp"
#include "GLFW/glfw3.h"

App::App(int window_width, int window_height, std::string name)
{
    // REDIMENSIONNEMENT DE LA FENÊTRE
    size_callback(window_width, window_height);

    // LOAD OF THE TEXTURES
    earthPic = glimac::loadImage("/home/utilisateur/Documents/S3-SYNTHESE_DIMAGE/Simple-Glimac-Setup-main/assets/textures/EarthMap.jpg");
    if(earthPic == NULL) std::cout << "Erreur: le chargement de la texture de terre a échoué." << std::endl;

    cloudsPic = glimac::loadImage("/home/utilisateur/Documents/S3-SYNTHESE_DIMAGE/Simple-Glimac-Setup-main/assets/textures/CloudMap.jpg");
    if(earthPic == NULL) std::cout << "Erreur: le chargement de la texture des nuages a échoué." << std::endl;

    moonPic = glimac::loadImage("/home/utilisateur/Documents/S3-SYNTHESE_DIMAGE/Simple-Glimac-Setup-main/assets/textures/MoonMap.jpg");
    if(earthPic == NULL) std::cout << "Erreur: le chargement de la texture de lune a échoué." << std::endl;

    glGenTextures(1, &earthTex);
    glBindTexture(GL_TEXTURE_2D, earthTex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            earthPic->getWidth(),
            earthPic->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            earthPic->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &cloudsTex);
    glBindTexture(GL_TEXTURE_2D, cloudsTex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            cloudsPic->getWidth(),
            cloudsPic->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            cloudsPic->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &moonTex);
    glBindTexture(GL_TEXTURE_2D, moonTex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            moonPic->getWidth(),
            moonPic->getHeight(),
            0,
            GL_RGBA,
            GL_FLOAT,
            moonPic->getPixels()
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // LOADING OF THE SHADERS
    // (VERTEX SHADER + FRAGMENT SHADER)
    glimac::FilePath applicationPath(name);
    earthProgram = EarthProgram(applicationPath);
    moonProgram = MoonProgram(applicationPath);

    glEnable(GL_DEPTH_TEST);

    // INITIALISATION DES VARIABLES
    // projection matrix
    projMatrix = glm::perspective(
        glm::radians(70.f),
        float(window_width/window_height),
        0.1f,
        100.f
    );

    // earth model view matrix
    mvMatrix = glm::mat4(1.0f);
    
    // Variables de la scène
    sphere = glimac::Sphere(1,30,15);

    

    // INITIALIZATION OF THE VBO
    // Le "Vertex Buffer Object" est un tableau
    // stocké sur le GPU contenant les sommets des
    // primitives (triangles)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(
            GL_ARRAY_BUFFER,
            sphere.getVertexCount()*sizeof(glimac::ShapeVertex),
            sphere.getDataPointer(),
            GL_STATIC_DRAW
        );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // INITIALIZATION OF THE VAO
    // Le "Vertex Array Object" décrit la manière
    // dont les données brutes contenus dans le VBO
    // doivent être interprétées par le GPU
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);

        // POSITION PARAM CREATION
        const GLuint VERTEX_ATTR_POSITION = 0;
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

        // NORMAL PARAM CREATION
        const GLuint VERTEX_ATTR_NORMAL = 1;
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

        // TEXCOORDS PARAM CREATION
        const GLuint VERTEX_ATTR_TEXCOORDS = 2;
        glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);

        // On relie les données brutes (VBO) à
        // l'interpréteur (VAO) via un "binding"
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
            // POSITION
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, position));

            // NORMAL
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, normal));

            // TEXCOORDS
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, texCoords));
                  
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    for(int i=0; i < 32; ++i)
    {
        const float radius = 0.2;
        const float min = 0.0, max = 360.0;
        randomAxis.push_back(glm::sphericalRand(radius));
        startPos.push_back(glm::linearRand(min, max));
    }
}

void App::render()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);
        glm::mat4 viewMatrix = trackballCamera.getViewMatrix();
        earthProgram.m_Program.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, earthTex);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, cloudsTex);
        glUniform1i(earthProgram.uEarthTexture, 0);
        glUniform1i(earthProgram.uCloudTexture, 1);

        // MODEL MATRIX
        glm::mat4 earthMVMatrix = glm::rotate(
            mvMatrix,
            glimac::getTime(),
            glm::vec3(0.0,1.0,0.0)
        );

        glUniformMatrix4fv(
            earthProgram.uMVMatrix,
            1,
            GL_FALSE,
            glm::value_ptr(earthMVMatrix)
        );
        
        // NORMAL MATRIX
        glUniformMatrix4fv(
            earthProgram.uNormalMatrix,
            1,
            GL_FALSE,
            glm::value_ptr(
                glm::transpose(
                    glm::inverse(earthMVMatrix)
                )
            )
        );

        // MVP MATRIX
        glUniformMatrix4fv(
            earthProgram.uMVPMatrix,
            1,
            GL_FALSE,
            glm::value_ptr(projMatrix * viewMatrix * earthMVMatrix)
        );

        glDrawArrays(
            GL_TRIANGLES,
            0,
            sphere.getVertexCount()
        );
        
        moonProgram.m_Program.use();
        for(int i=0; i<32; ++i)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, moonTex);
            glUniform1i(moonProgram.uTexture, 0);

            glm::mat4 moonMVMatrix = glm::rotate(mvMatrix, glimac::getTime() + startPos[i], randomAxis[i]); // Translation * Rotation
            moonMVMatrix = glm::translate(moonMVMatrix, glm::vec3(-2, 0, 0)); // Translation * Rotation * Translation
            moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

            // MODEL MATRIX
            glm::mat4 moonNormalMatrix = glm::transpose(
                glm::inverse(moonMVMatrix)
            );

            glUniformMatrix4fv(
                moonProgram.uMVMatrix,
                1,
                GL_FALSE,
                glm::value_ptr(moonMVMatrix)
            );

            // NORMAL MATRIX
            glUniformMatrix4fv(
                moonProgram.uNormalMatrix,
                1,
                GL_FALSE,
                glm::value_ptr(moonNormalMatrix)
            );

            // MVP MATRIX
            glUniformMatrix4fv(
                moonProgram.uMVPMatrix,
                1,
                GL_FALSE,
                glm::value_ptr(projMatrix * viewMatrix * moonMVMatrix)
            );

            glDrawArrays(
                GL_TRIANGLES,
                0,
                sphere.getVertexCount()
            );
            
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    glBindVertexArray(0);
}

void App::key_callback(int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case 262:
        if(action > 0) trackballCamera.rotateSide(10);
        break;
    case 263:
        if(action > 0) trackballCamera.rotateSide(-10);
        break;
    case 264:
        if(action > 0) trackballCamera.rotateUp(-10);
        break;
    case 265:
        if(action > 0) trackballCamera.rotateUp(10);
        break;

    default:
        break;
    }
}

void App::mouse_button_callback(int button, int action, int mods)
{
    if(button == 0 /* CLICK GAUCHE */)
    {
        trackballCamera.rotateSide(-10);
    }
    else
    {
        trackballCamera.rotateSide(10);
    }
}

void App::scroll_callback(double xoffset, double yoffset)
{
    trackballCamera.moveFront(yoffset);
}

void App::cursor_position_callback(double xpos, double ypos)
{
     
}

void App::size_callback(int width, int height)
{
    _width  = width;
    _height = height;
}

void App::destroy()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &earthTex);
}