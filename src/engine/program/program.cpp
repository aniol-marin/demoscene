#include "program.h"

namespace MoleDemo
{
    using namespace mole_def;

    Program::Program(const Screen& screen) : status{ ProgramStatus::RUNNING }, m_screen{ screen } {}

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
        return ProgramStatus::RUNNING == status;
    }
}
