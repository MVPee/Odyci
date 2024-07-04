# include <iostream>
# include <GLFW/glfw3.h>
# include "includes/Window.hpp"

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    std::cout << key << std::endl;
}

int main(void)
{
    try {
        Window Window("Odyci", 800, 800);

        while (!glfwWindowShouldClose(Window.getWindow())) {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(Window.getWindow());
            glfwPollEvents();

            glfwSetKeyCallback(Window.getWindow(), key_callback);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}