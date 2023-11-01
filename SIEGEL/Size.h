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
	protected:
		Position& GetPosition(GO& object);
		Vector2f &GetMargin(GO& object);

		friend GO;
	public:
		double getSize();
		void setSize(double size);
		Size(double size);
		Size();
		virtual Vector2f GetBounds(Vector2f &parentBounds, GO &object) = 0;
		virtual double GetMinParentSize(double maxParentSize, GO &object);
		virtual double SizeToParentSize(double size, double maxParentSize, GO &object);
	};
}