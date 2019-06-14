#include "InputLayer.h"

// Appends this layer to the specified layer.
void InputLayer::appendTo(NetLayer* layer)
{
	throw std::runtime_error("InputLayer: Input MUST be the first layer.");
}