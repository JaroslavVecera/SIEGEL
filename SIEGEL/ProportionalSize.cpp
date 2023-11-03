#pragma once

#include "ProportionalSize.h"

siegel::ProportionalSize::ProportionalSize(double size, double proportion) : StretchableSize(size) {
	_proportion = proportion;
}

double siegel::ProportionalSize::GetFactor(double factor1, double factor2) {
	return _proportion * fmax(1, fmin(factor1, factor2));
}