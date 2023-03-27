module effects;

namespace MoleDemo {
	Fire::Fire(Timer* timer, Screen* screen) :
		Effect{ timer, screen }
	{
	}

	Fire::~Fire() {
	}

	void Fire::Load() {
		srand(0);
		ClearBuffer(0x55005500);
		ClearBuffer(0x55005500, first);
		ClearBuffer(0x55005500, second);
	}

	void Fire::Unload() {
	}

	void Fire::Update(uint_fast16_t intensity) {
	}

	void Fire::Cache(std::vector<bool>& mask) {
	}

	void  Fire::GeneratePalette() {

	}

	void  Fire::GenerateHotspots() {

		uint_fast16_t start{ (uint_fast16_t)(rand() % screen->w) };
		uint_fast16_t end{ std::min(start + (uint_fast16_t)(rand() % 256), (uint_fast16_t)screen->w) };
		Color random{};

		for (uint_fast8_t i = start; i < end; ++i) {

			uint_fast16_t i1{ GetPixel(Point2D{i, (uint_fast16_t)(screen->h - 1)}) };
			uint_fast16_t i2{ GetPixel(Point2D{i, (uint_fast16_t)(screen->h - 2)}) };
			uint_fast16_t i3{ GetPixel(Point2D{i, (uint_fast16_t)(screen->h - 3)}) };

			random.SetRGBA(
				(uint8_t)(200 + (rand() % 55)),
				(uint8_t)(50 + (rand() % 55)),
				(uint8_t)(50 + (rand() % 55)));
			first[i1] = random.rgba();
			first[i2] = random.rgba();
			first[i3] = random.rgba();

		}
	}

	void Fire::FilterPrevious() {

	}
}

