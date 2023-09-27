#pragma once

#include "Size.h"
#include "Position.h"

namespace siegel {
	class Size;
	class siegel::FixedSize : public Size {
	public:
		FixedSize(double size);

		virtual Vector2f GetBounds(Vector2f& parentBounds, Position& position, const  forward_list<GO*>& children);
	};
}