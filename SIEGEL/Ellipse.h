#pragma once

#include "GO.h"
#include "Shape.h"
#include "Canvas.h"
#include "EllipseShape.h"

namespace siegel {
	class Ellipse : public Shape {
	protected:
		EllipseShape _shape;
		void SetRadius(const sf::Vector2f& radius);
		const sf::Vector2f& GetRadius() const;
		void Initialize(sf::Vector2f& radius, sf::Color color);
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
	public:
		Ellipse();
		Ellipse(sf::Vector2f& radius, sf::Color color);

		void SetColor(const Color color);
		const Color GetColor() const;


		virtual const FloatRect GetLocalBounds();
		virtual const FloatRect GetGlobalBounds();

		void Render();
	};
}