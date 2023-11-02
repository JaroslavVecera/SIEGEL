#pragma once

#include "GO.h"
#include "Canvas.h"
#include <forward_list>

namespace siegel {
	class Canvas;
	class Layout : public GO {
	protected:
		forward_list<GO*> _children;
		RectangleShape _border;
		double _borderThickness;
		sf::Color _outlineColor;
	protected:
		void Initialize();
		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		virtual void EmplaceBorder();
		virtual forward_list<GO*> GetChildren();
	public:
		Layout();
		void SetHorizontalSize(siegel::Size* size);
		void SetVerticalSize(siegel::Size* size);
		void SetOutlineColor(Color& c);
		Color GetOutlineColor() const;
		void AddChild(GO* child);
		virtual void Render() const;
		void SetHorizontalPadding(Vector2f margin);
		void SetVerticalPadding(Vector2f margin);
		virtual Vector2f &GetHorizontalPadding();
		virtual Vector2f &GetVerticalPadding();
		void SetBorderThickness(double thickness);
		virtual double GetBorderThickness();
	};
}