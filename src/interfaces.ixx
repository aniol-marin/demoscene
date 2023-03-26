export module interfaces;

import <string>;

namespace MoleDemo {

	export struct Initializable {
		virtual void Init() = 0;
		virtual void Finalize() = 0;
	};

	export struct Loadable {
		virtual void Load(std::string source) = 0;
		virtual void Unload() = 0;
	};
}