#pragma once

#include <type_traits>
#include <cmath>

template<typename T>
struct BasicSize {
	T width;
	T height;
	BasicSize()
		:width(0), height(0) {}

	BasicSize(T width, T height)
		: width(width), height(height) {}
};

typedef  BasicSize<int> Size; 
