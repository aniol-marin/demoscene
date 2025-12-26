#ifndef MOLE_PROGRAM_H
#define MOLE_PROGRAM_H

#include "definitions.h"

namespace MoleDemo
{
    using namespace mole_def;

    class Program
    {
        ProgramStatus status;
	/*
        const Screen m_screen;
	 */

    public:
	Program();
	/*
        Program(const Screen& screen);
	 */
        Program(const Program&);
        ~Program();

        void SetStatus(ProgramStatus status);
	/*
        const Screen* GetScreen() const;
	 */
        bool Running();
    };
}

#endif
