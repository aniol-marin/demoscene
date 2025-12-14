#ifndef MOLE_GLFW_WRAPPER_H
#define MOLE_GLFW_WRAPPER_H

extern "C" {
#include "GLFW/glfw3.h"
}
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "definitions.h"

namespace mole::graphics
{
    using proc_address = decltype(glfwGetProcAddress);
    using size_1D = std::uint_fast16_t;
    using callback = std::function<void(void)>;

    struct Vector2
    {
        float x, y;
    };
    struct window_size
    {
        const size_1D w, h;
    };
    const std::string name{ "test" };
    constexpr auto width{ 480 };
    constexpr auto height{ 640 };
    static std::map<char, std::vector<callback>> callbacks;
    static std::vector<callback> MouseButtonCallbacks_v;
    static std::map<char, std::vector<callback>> MouseButtonCallbacks;
    static std::map<int, std::vector<callback>> MouseCursorPosCallbacks;
    static Vector2 delta;

    struct WindowContext
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
        void AddCallback(const char key, callback&& callback) { callbacks[key].emplace_back(std::move(callback)); }
        void PollEvents();
    };
}

#endif
