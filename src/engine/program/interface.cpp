export module program;

import definitions;

namespace MoleDemo
{
	export class Program;
}

class MoleDemo::Program
{
	ProgramStatus status;
	const Screen& m_screen;

public:
	Program(const Program&) = delete;
	Program(const Screen& screen);
	Program(Program&&) = default;
	~Program() = default;

	void SetStatus(ProgramStatus status);
	const Screen* GetScreen() const;
	bool Running();
};
