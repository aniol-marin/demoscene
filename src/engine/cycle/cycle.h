#ifndef MOLE_CYCLE_H
#define MOLE_CYCLE_H

#include "Effect.h"
#include "definitions.h"
#include "input.h"
#include "program.h"
#include "render.h"
#include "renderables.h"
#include "timer.h"

using namespace mole_def;

namespace MoleDemo
{
    class Cycle
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
}

#endif
