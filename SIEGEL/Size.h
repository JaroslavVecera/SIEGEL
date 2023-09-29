#pragma once
#include "SFML/Graphics.hpp"
#include <forward_list>
#include "GO.h"

using namespace sf;

namespace siegel {
	class Position;
	class GO;

	enum class SizeType {
		Horizontal,
		Vertical
	};

	class Size {
	protected:
		double _size;
		SizeType _type;

		friend GO;
	public:
		double getSize();
		void setSize(double size);
		Size(double size);
		Size();
		virtual Vector2f GetBounds(Vector2f const& parentBounds, Position const& position, const std::forward_list<GO*> const& children) = 0;
		virtual double GetMinParentSize(double maxParentSize, Position const& position, std::forward_list<GO*> const& children);
		virtual double SizeToParentSize(double size, double maxParentSize, Position const& position, std::forward_list<GO*> const& children);
	};
}