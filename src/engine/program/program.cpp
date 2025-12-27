#include "program.h"

#include <exception>

namespace MoleDemo
{
    using namespace mole_def;

    Program::Program(const Screen& screen) : status(PROGRAM_RUNNING), m_screen(screen) {}

    Program::Program(const Program& other) : status(other.status), m_screen(other.m_screen)
    {
        throw std::exception();
    }

    Program::~Program() {}

    void Program::SetStatus(ProgramStatus status)
    {
        this->status = status;
    }

    const Screen* Program::GetScreen() const
    {
        return &m_screen;
    }

    bool Program::Running()
    {
        return PROGRAM_RUNNING == status;
    }
}
