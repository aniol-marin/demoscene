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
	}

	void Fire::Unload() {
	}

	void Fire::Update(uint_fast16_t intensity) {
	}

	void Fire::Cache(std::vector<bool>& mask) {
	}
}

