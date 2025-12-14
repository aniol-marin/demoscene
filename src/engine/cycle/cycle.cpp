module;

#include <vector>

module cycle;

import definitions;
import effect;
import renderables;
import timer;
import program;
import input;
import render;
using namespace mole_def;

namespace MoleDemo
{
    Cycle::Cycle(Program& program, Timer& timer, InputManager& input, RenderManager& render) :
      program{ program }, inputManager{ input }, renderManager{ render }, timer{ timer }
    {
    }

    void Cycle::PollEvents()
    {
        if (timer.EndReached())
        {
            program.SetStatus(ProgramStatus::TERMINATE_OK);
        }
        else
        {
            program.SetStatus(inputManager.PollEvents());
        }
    }

    void Cycle::Update(permille intensity)
    {
        for (Renderable* renderable: renderables)
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
        renderables.insert(renderables.begin(), aRenderables.cbegin(), aRenderables.cend());
    }
}
