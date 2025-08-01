#include "glfw_wrapper.h"

#include "GLFW/glfw3.h"

using callback = std::function<void(void)>;
namespace mole::graphics
{
    using size_1D = std::uint_fast16_t;

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

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
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
        /*
        static Vector2 previous{ (float) x, (float) y };

        const Vector2 c{ (float) x, (float) y };
        delta = { c.x - previous.x, c.y - previous.y };
        previous = c;

        for (callback& callback: mousescroll)
        {
            callback();
        }
        */
    }
}
