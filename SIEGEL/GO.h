#pragma once

#include "SFML/Graphics.hpp"
#include "Position.h"
#include "Size.h"

using namespace std;
using namespace sf;

namespace siegel {
	class Canvas;
	class Position;
	class Size;
	class FixedSize;
	class ShrinkableSize;
	class Layout;

	class GO {
	protected:
		Canvas* _window;
		Position _horizontalPosition;
		Position _verticalPosition;
		Size* _verticalSize;
		Size* _horizontalSize;
		Vector2f _horizontalMargin;
		Vector2f _verticalMargin;
		Vector2f _canvasTopleft;
		Vector2f _canvasSize;
		Vector2f _canvasHorizontalBounds;
		Vector2f _canvasVerticalBounds;
	protected:
		void SetWindow();
		void Initialize();

		virtual void Emplace(Vector2f& horizontalParentBounds, Vector2f& verticalParentBounds);
		virtual forward_list<GO*> GetChildren();
		friend Layout;
		friend Canvas;
		friend ShrinkableSize;
		friend Size;
	public:
		GO();
		~GO();

		void SetHorizontalPosition(siegel::Position &position);
		siegel::Position& GetHorizontalPosition();
		void SetVerticalPosition(siegel::Position& position);
		siegel::Position& GetVerticalPosition();
		siegel::Size& GetHorizontalSize() const;
		siegel::Size& GetVerticalSize() const;
		void SetHorizontalSize(siegel::Size* size);
		void SetVerticalSize(siegel::Size* size);
		void SetHorizontalMargin(Vector2f margin);
		void SetVerticalMargin(Vector2f margin);
		Vector2f &GetHorizontalMargin();
		Vector2f &GetVerticalMargin();
		virtual void Render() const = 0;
		double virtual GetBorderThickness();
	};
}