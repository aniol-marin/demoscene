#ifndef MOLE_PROGRAM_H
#define MOLE_PROGRAM_H

#include "definitions.h"
/*
#include "loaders/screen_loader.h"
*/

namespace MoleDemo
{
    using namespace mole_def;

    class Program
    {
        ProgramStatus status;
        const Screen& m_screen;

    public:
        Program(const Screen& screen);
        Program(const Program&) = delete;
        Program(Program&&) = default;
        ~Program() = default;

        void SetStatus(ProgramStatus status);
        const Screen* GetScreen() const;
        bool Running();
    };
}

#endif
