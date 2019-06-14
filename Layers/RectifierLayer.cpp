#include "RectifierLayer.h"

// updates output from input
void RectifierLayer::processInput()
{
	if (!_prev)
		throw std::runtime_error("RectifierLayer: Missing previous layer.");

	// Rectification function
	_output = max(_prev->output(), 0.0f);
}

// updates error of the previous layer (call after each sample in batch).
void RectifierLayer::processError()
{
	if (!_prev)
		throw std::runtime_error("RectifierLayer: Missing previous layer.");

	// No parameters to update, only backpropagate
	_prev->error() = Matrix::elemProd(_prev->output() > 0.0f, _error);
}