# include "../includes/Window.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Window::Window(const char *name, int width, int height) {
    if (!glfwInit())
        throw WindowFailed(0);

    std::cout << "Constructor Window" << std::endl;
    
    this->_name = name;
    this->_height = height;
    this->_width = width;

    this->_window = glfwCreateWindow(this->_width, this->_height, this->_name, NULL, NULL);
    if (!this->_window) {
        glfwTerminate();
        throw WindowFailed(1);
    }

    glfwMakeContextCurrent(this->_window);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Window::~Window() {
    std::cout << "Destructor Window" << std::endl;
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
** --------------------------------- EXCEPTION --------------------------------
*/

Window::WindowFailed::WindowFailed(int errorCode) : _errorCode(errorCode) {}

const char* Window::WindowFailed::what() const throw() {
    if (_errorCode == 0)
        return "GLFW initialization failed.";
    return "Window creation failed.";
}