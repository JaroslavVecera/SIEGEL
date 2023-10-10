#pragma once

#include "Size.h"
#include "Position.h"

namespace siegel {
	class Size;
	class StretchableSize : public Size {
	public:
		StretchableSize(double size);

		virtual Vector2f GetBounds(Vector2f &parentBounds, GO &objct);
	};
}
