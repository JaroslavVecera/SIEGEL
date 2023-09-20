#pragma once

#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace siegel {
	class EllipseShape : public sf::Shape {
		sf::Vector2f m_radius;
	public:
		EllipseShape();
		EllipseShape(const Vector2f&);
		void setRadius(const sf::Vector2f& radius);
		const sf::Vector2f& getRadius() const;
		virtual std::size_t getPointCount() const;
		virtual sf::Vector2f getPoint(std::size_t index) const;
	};
}