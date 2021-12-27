#include "App.hpp"

//Dimension de la fenêtre
int window_width  = 720;
int window_height = 720;

static App& get_app(GLFWwindow* window)
{
    return *reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
}

int main(int argc, char** argv)
{   
    /* Initialize the library GLFW */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(
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


    /* Create the App */
    App app(window, window_width, window_height, argv[0]);

    /* Hook user inputs to the App */
    glfwSetWindowUserPointer(window, reinterpret_cast<void*>(&app));

    /* Hook input callbacks */
    /* Keyboard */ 
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){

        if(get_app(window).getGame().isRunning())
        {
            get_app(window).getGame().key_callback(key, scancode, action, mods);
        }
        else
        {
            get_app(window).key_callback(key, scancode, action, mods);
        }
    });
    /* Mouse Buttons */
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
        if(get_app(window).getGame().isRunning())
        {
            get_app(window).getGame().mouse_button_callback(button, action, mods);
        }
        else
        {
            get_app(window).mouse_button_callback(button, action, mods);
        }
    });

    /* Mouse scroll */
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset){
        if(get_app(window).getGame().isRunning())
        {
            get_app(window).getGame().scroll_callback(xoffset, yoffset);
        }
        else
        {
            get_app(window).scroll_callback(xoffset, yoffset);
        }
    });

    /* Cursor position */
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos){
        if(get_app(window).getGame().isRunning())
        {
            get_app(window).getGame().cursor_position_callback(xpos, ypos);
        }
        else
        {
            get_app(window).cursor_position_callback(xpos, ypos);
        }
    });

    /* Window resize */
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height){
        get_app(window).size_callback(window, width, height);
    });

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        app.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    
    return 0;
}