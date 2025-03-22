export module program;

import definitions;

namespace MoleDemo {

	export class Program;
}

class MoleDemo::Program {
	ProgramStatus status;
	const Screen m_screen;
public:
	Program() : Program{Screen{600, 450}} {}
	Program(const Screen& screen) :
		status{ ProgramStatus::RUNNING },
		m_screen{ screen } {}
	void SetStatus(ProgramStatus status) { this->status = status; }
	const Screen* GetScreen() const { return &m_screen; }
	bool Running() { return ProgramStatus::RUNNING == status; }
};
