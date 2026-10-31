#ifndef MOLE_GLFW_WRAPPER_H
#define MOLE_GLFW_WRAPPER_H

extern "C" {
#include "GLFW/glfw3.h"
}
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "definitions.h"

namespace mole::graphics
{
    typedef GLFWglproc (proc_address)(const char*);
    typedef unsigned short int size_1D;
    typedef void (*callback)();

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

    struct WindowContext
    {
        GLFWwindow* window{ NULL };
        const window_size size;
        const std::string name;
        proc_address* address;

        WindowContext() = delete;
        WindowContext(window_size&& size, const std::string& name);
        WindowContext(const WindowContext&) = delete;
        WindowContext(WindowContext&&) = default;
        ~WindowContext();

        void Swap() const { glfwSwapBuffers(window); }
        void AddCallback(const char key, callback&& callback) { callbacks[key].emplace_back(std::move(callback)); }
        void PollEvents();
    };
}

#endif
