#include "editor.h"

namespace mole::editor
{
	void redirect()
	{
	}

    Context::Context() : context{ { 640, 480 }, "MoleDemo Editor" }, render{ context }, ui{ context }
    {
        const char key = 0;
        context.AddCallback(key, redirect);
    }

    [[nodiscard]] bool Context::is_active()
    {
        return active;
    }
    void Context::PollEvents()
    {
        context.PollEvents();
    }

    void Context::Draw()
    {
        render.Render();
        ui.RenderUI();
        context.Swap();
    }
}
