#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

namespace siegel {
	class Position;

	class Size {
	protected:
		double _size;
	public:
		double getSize();
		void setSize(double size);

		Size(double size);
		Size();

		virtual Vector2f GetBounds(Vector2f& parentBounds, Position& position) = 0;
	};
}
