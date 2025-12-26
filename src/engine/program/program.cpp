#include "program.h"

#include <exception>

namespace MoleDemo
{
    using namespace mole_def;

    Program::Program()
	    : status( PROGRAM_RUNNING )
	      /*
		 Program::Program(const Screen& screen)
	    , m_screen( screen )
	    */
    {
    }

    Program::Program(const Program& other)
	    : status( other.status )
	      /*
	    , m_screen( other.screen )
	    */
    {
	    throw std::exception();
    }

    Program::~Program()
    {
    }

    void Program::SetStatus(ProgramStatus status)
    {
        this->status = status;
    }

	      /*
    const Screen* Program::GetScreen() const
    {
        return &m_screen;
    }
    */

    bool Program::Running()
    {
        return PROGRAM_RUNNING == status;
    }
}
