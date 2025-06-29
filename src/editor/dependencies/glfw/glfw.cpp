module;

extern "C" {
#include "GLFW/glfw3.h"
}

export module glfw_wrapper;

import std;

namespace mole::graphics
{

    static void ErrorCallback(int code, const char* message) {}
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {}
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {}
    static void MouseCursorPosCallback(GLFWwindow* window, double x, double y) {}

    struct Context
    {
        GLFWwindow* window{ NULL };
    };

    export Context create_context()
    {
        Context context{};
	auto& window{ context.window };
	std::string name { "test" };
	auto width { 480 };
	auto height { 640 };

        std::cout << "[MOCK] create context\n";
        glfwSetErrorCallback(ErrorCallback);

        glfwInit();
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_DEPTH_BITS, 16);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            std::cout << "[FAIL] failed to create the window\n";
        }
        else
        {
            glfwSetWindowPos(window, 200, 10);

            glfwSetKeyCallback(window, KeyCallback);
            glfwSetMouseButtonCallback(window, MouseButtonCallback);
            glfwSetCursorPosCallback(window, MouseCursorPosCallback);

            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);
        }

        return {};
    }
}
