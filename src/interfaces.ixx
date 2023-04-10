export module interfaces;

import definitions;
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

	export struct Renderable {
		virtual void Update(permille intenisty, permille deltaTime) = 0;
		virtual void Cache(StencilBuffer& mask) = 0;
		virtual rgbaColor GetPixel(Point2D point) = 0;
		virtual rgbaColor GetPixel(index index) = 0;
		virtual BlendMode GetBlend() = 0;
		virtual bool CheckStencil(index index) = 0;
	};
}