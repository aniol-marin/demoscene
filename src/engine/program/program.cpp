#include "program.h"
/*
#include "loaders/screen_loader.h"
*/

class MoleDemo::Program
{
	ProgramStatus status;
	const Screen& m_screen;

public:
	Program(const Screen& screen) :
		status{ ProgramStatus::RUNNING },
		m_screen{ screen }
	{
	}
	Program(const Program&) = delete;
	Program(Program&&) = default;
	~Program() = default;

	void SetStatus(ProgramStatus status) { this->status = status; }
	const Screen* GetScreen() const { return &m_screen; }
	bool Running() { return ProgramStatus::RUNNING == status; }
};
>>>>>>> origin/feature/linux-port
