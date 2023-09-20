#pragma once

#include "Size.h"

using namespace siegel;


Size::Size(double size) {
	setSize(size);
}

Size::Size() {
	setSize(0);
}

double Size::getSize() {
	return _size;
}

void Size::setSize(double size) {
	_size = size;
}
