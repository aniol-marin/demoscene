export module chess;

import std;
import effect;

namespace MoleDemo
{
    export class ChessBoard;
}

namespace MoleDemo
{
    using namespace mole_def;

    class ChessBoard
      : public Texturable
      , public Effect
    {
        Color A, B;
        bunch repetitions{ 1 };

    public:
        ChessBoard() = delete;
        ChessBoard(Timer* timer, Screen* screen);
        ~ChessBoard() override = default;

        void Set(Color A, Color B, bunch repetitions);

        void Load() override;
        void Unload() override;
        void Update(permille intensity, milliseconds delta) override;
        void Cache(StencilBuffer& mask) override;
        rgbaColor GetMappedUV(CoordinateUV uv) override;
    };
}
