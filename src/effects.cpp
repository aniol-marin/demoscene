export module effects;

export import effect;
export import solid;
export import stars;
export import gradient;
export import wheel;
export import chess;
export import plasma;
export import noise;
export import tunel;

	/*
	// regular effects
	export class Fire;
	// customizables
	export class Plasma;
	export class Tunel;
	// texturizables
	export class ChessBoard;
	export class RandomNoise;
	*/

/*
class MoleDemo::Fire : public Effect {

	PixelBuffer firstBuffer;
	PixelBuffer secondBuffer;
	std::vector<Color> palette;

	void GeneratePalette();
	void GenerateHotspots(PixelBuffer& buffer, permille intensity);
	void FilterPrevious(PixelBuffer& src, PixelBuffer& dest, milliseconds delta, permille intensity);

public:
	Fire(Timer* timer, Screen* screen);
	~Fire();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
};

*/

