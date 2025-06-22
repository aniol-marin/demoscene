export module cycle;

import std;
import definitions;
import effect;
import renderables;
import timer;
import program;
import input;
import render;

namespace MoleDemo
{
    export class Cycle;
}

class MoleDemo::Cycle
{
    Renderables renderables{};
    Program& program;
    Timer& timer;
    InputManager& inputManager;
    RenderManager& renderManager;

public:
    Cycle() = delete;
    Cycle(Program& program, Timer& timer, InputManager& input, RenderManager& render);
    Cycle(const Cycle&) = delete;
    Cycle(Cycle&&) = default;
    ~Cycle() = default;

    void PollEvents();
    void Update(permille intensity);
    void Draw();
    void Synch();
    void SetRenderables(const Renderables& aRenderables);
};

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
