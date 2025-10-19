module;

/*
#include "GLFW/glfw3.h"
 */

export module glfw_wrapper;

import std;
import definitions;

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

/*
    static void ErrorCallback(int code, const char* message);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void MouseCursorPosCallback(GLFWwindow* window, double x, double y);

    export using proc_address = decltype(glfwGetProcAddress);
 */
    export struct WindowContext
    {
/*
        GLFWwindow* window{ NULL };
 */
        const window_size size;
        const std::string_view name;
	/*
        proc_address* address;
	*/

        WindowContext() = delete;
        WindowContext(window_size&& size, std::string_view name);
        WindowContext(const WindowContext&) = delete;
        WindowContext(WindowContext&&) = default;
        ~WindowContext();

	/*
        void Swap() const { glfwSwapBuffers(window); }
	 */
        void AddCallback(const char key, callback&& callback) { callbacks[key].emplace_back(std::move(callback)); }
        void PollEvents();
    };
}
