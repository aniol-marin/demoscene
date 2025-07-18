module;

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

export module imgui_wrapper;

namespace mole::ui
{
    export int test()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        return 0;
    }
}
