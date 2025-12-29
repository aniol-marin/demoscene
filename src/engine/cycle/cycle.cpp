#include "cycle.h"
using namespace mole_def;

namespace MoleDemo
{
    Cycle::Cycle(Program& program, Timer& timer, InputManager& input, RenderManager& render) :
      program(program), inputManager(input), renderManager(render), timer(timer)
    {
    }

    void Cycle::PollEvents()
    {
        if (timer.EndReached())
        {
            program.SetStatus(mole_def::PROGRAM_TERMINATE_OK);
        }
        else
        {
            program.SetStatus(inputManager.PollEvents());
        }
    }

    void Cycle::Update(permille intensity)
    {
        for (Renderable* renderable = *renderables.begin(); renderable != *renderables.end(); ++renderable)
        {
            renderable->Update(intensity, timer.GetDeltaTime());
        }
    }

    void Cycle::Draw()
    {
        renderManager.Draw(renderables);
    }

    void Cycle::Synch()
    {
        timer.WaitUntilNextFrame();
    }

    void Cycle::SetRenderables(const Renderables& aRenderables)
    {
        renderables.clear();
        renderables.insert(renderables.begin(), aRenderables.begin(), aRenderables.end());
    }
}
