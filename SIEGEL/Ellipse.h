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
	protected:
		void Initialize(const sf::Vector2f& radius, sf::Color color);
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
	public:
		Ellipse();
		Ellipse(const sf::Vector2f& radius, sf::Color color);

		void SetColor(const Color color);
		const Color GetColor() const;
		virtual const FloatRect GetLocalBounds() const;
		virtual const FloatRect GetGlobalBounds() const;
		virtual void Render() const;
	};
}