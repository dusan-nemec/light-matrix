#include "TanhLayer.h"

// updates output from input
void TanhLayer::processInput()
{
	if (!_prev)
		throw std::runtime_error("RectifierLayer: Missing previous layer.");

	// Hyperbolic tangent
	_output = tanh(_prev->output());
}

// updates error of the previous layer (call after each sample in batch).
void TanhLayer::processError()
{
	if (!_prev)
		throw std::runtime_error("RectifierLayer: Missing previous layer.");

	// No parameters to update, only backpropagate e_prev = dE/dx = dE/dy * dy/dx = e * (1 - y^2)
	_prev->error() = Matrix::elemProd(Matrix::elemProd(_output, _output), _error);
}