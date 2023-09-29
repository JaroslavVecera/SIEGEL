#pragma once

#include "Size.h"
#include "Position.h" 

namespace siegel {
	class ShrinkableSize : public Size {
	public:
		ShrinkableSize(double size);

		virtual Vector2f GetBounds(Vector2f const& parentBounds, Position const& position, const forward_list<GO*> const& children);
		virtual double GetMinParentSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children);
		virtual double GetMinSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children);
	};
}