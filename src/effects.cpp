export module effects;

export import effect;
export import solid;
export import stars;
export import gradient;
import std;
import definitions;
import timer;

namespace MoleDemo {

	/*
	// regular effects
	export class Stars;
	export class Fire;
	// customizables
	export class Plasma;
	export class Tunel;
	// texturizables
	export class Solid;
	export class Gradient;
	export class Wheel;
	export class ChessBoard;
	export class RandomNoise;

	class Star;
	*/
}

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

class MoleDemo::Plasma :
	public Customizable,
	public Effect {
	long long accumulatedTime{};
	std::vector<channel> plasma1;
	std::vector<channel> plasma2;
	int Windowx1, Windowy1, Windowx2, Windowy2;
	long src1, src2;
	Color palette[256];

	void buildPalette(uint16_t time);

public:
	Plasma(Timer* timer, Screen* screen);
	~Plasma();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	constexpr Id TextureLimit() const override { return 2; }
	void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
};

class MoleDemo::Tunel :
	public Customizable,
	public Effect {
	long long accumulatedTime{};
	std::vector<channel> Tunel1;
	std::vector<Point2D> uv;
	int Windowx1, Windowy1, Windowx2, Windowy2;
	long src1, src2;
	Color palette[256];
	std::unique_ptr<Texturable> texture;

	permille du, dv, speedU, speedV;

	void buildPalette(uint16_t time);

public:
	Tunel(Timer* timer, Screen* screen);
	~Tunel();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	constexpr Id TextureLimit() const override { return 1; }
	void AssignTexture(std::unique_ptr<Texturable> texture, Id id) override;
};
*/

/*

class MoleDemo::ChessBoard :
	public Texturable,
	public Effect {
	Color A, B;
	bunch repetitions;

public:
	ChessBoard();
	ChessBoard(Timer* timer, Screen* screen);
	~ChessBoard();

	void Set(Color A, Color B, bunch repetitions);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

class MoleDemo::RandomNoise :
	public Texturable,
	public Effect {
	ChannelBuffer noise;
	Color A, B;
	bunch repetitions;

public:
	RandomNoise();
	RandomNoise(Timer* timer, Screen* screen);
	~RandomNoise();

	void Set(Color a, Color b, bunch repetitions);

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetMappedUV(CoordinateUV uv) override;
};

class MoleDemo::Wheel : public Effect {
	Color color;
	Color base;
	Color top;
	rgbaColor rgbColor;
	double rotation;
	void SetColor();

public:
	Wheel(Timer* timer, Screen* screen);
	~Wheel();

	void Load() override;
	void Unload() override;
	void Update(permille intensity, milliseconds delta) override;
	void Cache(StencilBuffer& mask)  override;
	rgbaColor GetPixel(Point2D p) override;
	rgbaColor GetPixel(index index) override;
};

*/

