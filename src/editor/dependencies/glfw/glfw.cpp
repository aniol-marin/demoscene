#include "glfw_wrapper.h"

#include "GLFW/glfw3.h"

using callback = std::function<void(void)>;
namespace mole::graphics
{
    export using size_1D = std::uint_fast16_t;
    struct Vector2
    {
        float x, y;
    };
    struct window_size
    {
        const size_1D w, h;
    };
    constexpr std::string name{ "test" };
    constexpr auto width{ 480 };
    constexpr auto height{ 640 };
    static std::map<char, std::vector<callback>> callbacks;
    static std::vector<callback> MouseButtonCallbacks_v;
    static std::map<char, std::vector<callback>> MouseButtonCallbacks;
    static std::map<int, std::vector<callback>> MouseCursorPosCallbacks;
    static Vector2 delta;

    static void ErrorCallback(int code, const char* message);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseCursorPosCallback(GLFWwindow* window, double x, double y);

    export using proc_address = decltype(glfwGetProcAddress);
    export struct WindowContext
    {
        GLFWwindow* window{ NULL };
        const window_size size;
        const std::string_view name;
        proc_address* address;

        WindowContext() = delete;
        WindowContext(window_size&& size, std::string_view name);
        WindowContext(const WindowContext&) = delete;
        WindowContext(WindowContext&&) = default;
        ~WindowContext();

        void Swap() const { glfwSwapBuffers(window); }
        void PollEvents();
    };
}

namespace mole::graphics
{
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

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
        std::cout << "pressed: [" << std::to_string((char) key) << "] ";

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
        std::cout << "buttor pressed: [" << std::to_string(button) << "] ";

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
        std::cout << "[" << std::to_string(x) << "][" << std::to_string(y) << "] ";

        static Vector2 previous{ (float) x, (float) y };

        const Vector2 c{ (float) x, (float) y };
        delta = { c.x - previous.x, c.y - previous.y };
        previous = c;

        /*
                for (callback& callback: mousescroll)
                {
                    callback();
                }
            */
    }
}
