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
		Vector2f _horizontalPadding;
		Vector2f _verticalPadding;
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
		Vector2f GetHorizontalPadding();
		Vector2f GetVerticalPadding();
		void SetBorderThickness(double thickness);
		virtual double GetBorderThickness();
	};
}