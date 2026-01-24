#ifndef MOLE_INPUT_H
#define MOLE_INPUT_H

#include <exception>
#include "definitions.h"
#include "sdl_wrapper.h"

namespace MoleDemo
{
    struct InputManager;
} // namespace MoleDemo

using namespace mole_def;

class MoleDemo::InputManager
{
    SDL::SDLManager& manager;

public:
    InputManager(SDL::SDLManager& manager);
    ~InputManager() {}

    ProgramStatus PollEvents();
};

#endif //! MOLE_INPUT_H
