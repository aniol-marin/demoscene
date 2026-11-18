module;

#include "GLFW/glfw3.h"

export module glfw_wrapper;

import std;
import definitions;

using callback = std::function<void(void)>;

namespace mole::graphics
{
    export using proc_address = decltype(glfwGetProcAddress);
    export using size_1D = std::uint_fast16_t;

    export struct WindowContext;
}

namespace mole::graphics
{
    struct Vector2
    {
        float x, y;
    };
    struct window_size
    {
        const size_1D w, h;
    };
    constexpr std::string_view name{ "test" };
    constexpr auto width{ 480 };
    constexpr auto height{ 640 };

    struct WindowContext
    {
        GLFWwindow* window{ NULL };
        const window_size size;
        const std::string_view name;
        proc_address* address;

        WindowContext() = delete ("dependency injection is required for the invariant");
        WindowContext(window_size&& size, std::string_view name);
        WindowContext(const WindowContext&) = delete ("a single instance is allowed, move it instead");
        WindowContext(WindowContext&&) = default;
        ~WindowContext();

        void Swap() const { glfwSwapBuffers(window); }
        void AddCallback(const char key, callback&& callback);
        void PollEvents();
    };
}
