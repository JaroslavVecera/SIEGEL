#pragma once

#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace siegel {
	class RoundedRectangleShape : public sf::Shape {
	protected:
		sf::Vector2f _size;
		double _radius;
		mutable int _pointCount;
	public:
		RoundedRectangleShape();
		RoundedRectangleShape(const Vector2f& size, double radius);

		void SetRadius(double radius);
		double GetRadius() const;
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
		void setSize(const Vector2f& size);
		void Recompute();
	};
}