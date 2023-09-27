#pragma once

#include "Size.h"
#include "Position.h" 

namespace siegel {
	class ShrinkableSize : public Size {
	public:
		ShrinkableSize(double size);

		virtual Vector2f GetBounds(Vector2f& parentBounds, Position& position, const forward_list<GO*>& children);
		virtual double GetMinParentSize(double maxParentSize, Position& position, std::forward_list<GO*>& children);
		virtual double GetMinSize(double maxParentSize, Position& position, std::forward_list<GO*>& children);
	};
}