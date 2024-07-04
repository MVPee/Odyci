# include "../includes/Window.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Window::Window(const char *name, int width, int height) {
    if (!glfwInit())
        throw WindowFailed(0);

    //std::cout << "Constructor Window" << std::endl;
    
    this->_name = name;
    this->_height = height;
    this->_width = width;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->_window = glfwCreateWindow(this->_width, this->_height, this->_name, NULL, NULL);
    if (!this->_window) {
        glfwTerminate();
        throw WindowFailed(1);
    }

    glfwMakeContextCurrent(this->_window);
    glfwSetKeyCallback(this->_window, key_callback);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Window::~Window() {
    //std::cout << "Destructor Window" << std::endl;
    glfwDestroyWindow(this->_window);
    glfwTerminate();
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

GLFWwindow* Window::getWindow() {
    return (this->_window);
}

/*
** --------------------------------- CALLBACK ----------------------------------
*/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    //std::cout << key << std::endl;
}

/*
** --------------------------------- EXCEPTION --------------------------------
*/

Window::WindowFailed::WindowFailed(int errorCode) : _errorCode(errorCode) {}

const char* Window::WindowFailed::what() const throw() {
    if (_errorCode == 0)
        return "GLFW initialization failed.";
    return "Window creation failed.";
}