#ifndef MOLE_CHESSBOARD_H
#define MOLE_CHESSBOARD_H

#include "Effect.h"

namespace MoleDemo
{
    using namespace mole_def;

    class ChessBoard
      : public Texturable
      , public Effect
    {
        Color A, B;
        bunch repetitions;

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
#endif
