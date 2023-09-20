#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

namespace siegel {
	class FixedSize;
	class StretchableSize;
	class Position {
	protected:
		double _shift;
		double _proportionalParentOrigin;
		double _proportionalOrigin;

		double GetAbsoluteParentOrigin(Vector2f parentBounds) const;
	public:
		Position();
		Position(double shift, double proportionalParentOrigin, double proportionalOrigin);
		Position(double position);

		double GetShift() const;
		double GetProportionalParentOrigin() const;
		double GetProportionalOrigin() const;
		friend siegel::FixedSize;
		friend siegel::StretchableSize;
	};
}
