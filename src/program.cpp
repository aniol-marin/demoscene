export module program;

import definitions;

namespace MoleDemo {

	export class Program;
}

class MoleDemo::Program {
	ProgramStatus status;
	const Screen* const screen;
public:
	Program(Screen* screen) :
		status{ ProgramStatus::RUNNING },
		screen{ screen } {}
	void SetStatus(ProgramStatus status) { this->status = status; }
	const Screen* GetScreen() const { return screen; }
	bool Running() { return ProgramStatus::RUNNING == status; }
};
