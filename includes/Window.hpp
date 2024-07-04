#ifndef WINDOW_HPP
# define WINDOW_HPP

#include <iostream>
# include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow* _window;
        const char* _name;
        int         _height;
        int         _width;
    public:
        Window(const char *name, int height, int width);
        ~Window();

        GLFWwindow* getWindow();

        class WindowFailed : public std::exception {
            private:
                int _errorCode;
			public:
				WindowFailed(int errorCode);
                const char* what() const throw();
		};
};

#endif

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);