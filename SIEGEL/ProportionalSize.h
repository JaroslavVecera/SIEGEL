#pragma once

#include "Size.h"
#include "StretchableSize.h"
#include "Position.h"

namespace siegel {
	class Size;
	class ProportionalSize : public StretchableSize {
	protected:
		double _proportion;
		virtual double GetFactor(double factor1, double factor2);
	public:
		ProportionalSize(double size, double proportion);
	};
}