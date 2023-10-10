#pragma once

#include "Size.h"
#include "Position.h" 

namespace siegel {
	class ShrinkableSize : public Size {
	public:
		ShrinkableSize(double size);

		virtual Vector2f GetBounds(Vector2f &parentBounds, GO &object);
		virtual double GetMinParentSize(double maxParentSize, GO &object);
		virtual double GetMinSize(double maxParentSize, GO &object);
	};
}