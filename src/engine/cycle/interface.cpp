export module cycle;

import std;
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
