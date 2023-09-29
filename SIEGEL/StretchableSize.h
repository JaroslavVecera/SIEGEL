#pragma once

#include "Size.h"
#include "Position.h"

namespace siegel {
	class Size;
	class StretchableSize : public Size {
	public:
		StretchableSize(double size);

		virtual Vector2f GetBounds(Vector2f const& parentBounds, Position const& position, const forward_list<GO*> const& children);
	};
}
