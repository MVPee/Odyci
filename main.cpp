# include <iostream>
# include <GLFW/glfw3.h>
# include "includes/Window.hpp"

int main(void)
{
    try {
        Window Window("Odyci", 800, 800);

        while (!glfwWindowShouldClose(Window.getWindow())) {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(Window.getWindow());

            glfwPollEvents();
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}