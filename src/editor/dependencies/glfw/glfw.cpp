module;

#include "GLFW/glfw3.h"

module glfw_wrapper;

namespace mole::graphics
{
    static std::map<char, std::vector<callback>> callbacks;
    static std::map<char, std::vector<callback>> MouseButtonCallbacks;

    static void ErrorCallback(int code, const char* message);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseCursorPosCallback(GLFWwindow* window, double x, double y);
    static std::vector<callback> MouseButtonCallbacks_v;
    static std::map<int, std::vector<callback>> MouseCursorPosCallbacks;

    void WindowContext::AddCallback(const char key, callback&& callback)
    {
        callbacks[key].emplace_back(std::move(callback));
    }

    WindowContext::WindowContext(window_size&& size, std::string_view name) : size{ size }, name{ name }
    {
        glfwSetErrorCallback(ErrorCallback);

        glfwInit();
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_DEPTH_BITS, 16);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        window = glfwCreateWindow(width, height, std::string{ name }.c_str(), NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            std::cerr << "[FAIL] failed to create the window\n";
            throw std::exception{};
        }

        glfwSetWindowPos(window, 200, 10);

        glfwSetKeyCallback(window, KeyCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        glfwSetCursorPosCallback(window, MouseCursorPosCallback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        address = &glfwGetProcAddress;
    }

    WindowContext::~WindowContext()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void WindowContext::PollEvents()
    {
        glfwPollEvents();
    }

    void ErrorCallback(int code, const char* message)
    {
        std::cout << std::to_string(code) << ' ' << std::string{ message };
    }

    void KeyCallback(GLFWwindow*, int key, int scancode, int, int)
    {
        if (callbacks.count(key))
        {
            std::vector<callback>& actions = callbacks.at(key);
            for (callback& action: actions)
            {
                action();
            }
        }
    }

    void MouseButtonCallback(GLFWwindow* window, int button, int, int)
    {

        if (MouseButtonCallbacks.count(button))
        {
            auto& actions = MouseButtonCallbacks.at(button);
            for (callback& action: actions)
            {
                action();
            }
        }
    }

    void MouseCursorPosCallback(GLFWwindow* window, double x, double y)
    {
        static Vector2 previous{ (float) x, (float) y };

        const Vector2 c{ (float) x, (float) y };
        /*
            delta = { c.x - previous.x, c.y - previous.y };
         */
        previous = c;
    }
}
