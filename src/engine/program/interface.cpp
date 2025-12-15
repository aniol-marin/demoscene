export module program;

import definitions;

namespace MoleDemo
{
    export class Program;
}

namespace MoleDemo
{
    using namespace mole_def;

    class Program
    {
        ProgramStatus status;
        const Screen& m_screen;

    public:
        Program(const Screen& screen);
        Program(const Program&) = delete ("a single instance is allowed, move it instead");
        Program(Program&&) = default;
        ~Program() = default;

        void SetStatus(ProgramStatus status);
        const Screen* GetScreen() const;
        bool Running();
    };
}
