#include "SoftplusLayer.h"

// updates output from input
void SoftplusLayer::processInput()
{
	if (!_prev)
		throw std::runtime_error("SoftplusLayer: Missing previous layer.");

	// softplus function
	_output = softplus(_prev->output());
}

// updates error of the previous layer (call after each sample in batch).
void SoftplusLayer::processError()
{
	if (!_prev)
		throw std::runtime_error("SoftplusLayer: Missing previous layer.");

	// No parameters to update, only backpropagate err_prev = df/dx * err = sigmoid(x) .* err
	_prev->error() = Matrix::elemProd(sigmoid(_prev->output()), _error);
}