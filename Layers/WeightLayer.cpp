#include "WeightLayer.h"

// Constructs new weight layer with given output size and learning rule. Takes ownership of the learning rule.
// Note: input size of the layer will be computed when appended to another layer.
WeightLayer::WeightLayer(int size, LearningRule* learnRule)
	: NetLayer(size), _weights(), _gradients(), _learnRule(learnRule), _batchSize(0) {}

// Destructor
WeightLayer::~WeightLayer()
{
	delete _learnRule;
}

// Appends this layer to the specified layer.
void WeightLayer::appendTo(NetLayer* layer)
{
	// Use base method
	NetLayer::appendTo(layer);
	
	// Set the size of the layer
	_weights.resize(this->size(), _prev->size());
	_gradients.resize(this->size(), _prev->size());

	// Initialize weights
	_weights.rand(-1.0f, 1.0f);
	_gradients.clear();
}

// updates output from input
void WeightLayer::processInput()
{
	if (!_prev)
		throw std::runtime_error("WeightLayer: Missing previous layer.");

	// Calculate y = W * x
	_output = _weights * _prev->output();
}

// updates error of the previous layer (call after each sample in batch).
void WeightLayer::processError()
{
	if (!_prev)
		throw std::runtime_error("WeightLayer: Missing previous layer.");

	// 1. compute gradient dE/dW = e * de/dW = e * trans(x). Accumulate.
	_gradients += _error * _prev->output().t();
	_batchSize++;

	// 2. backpropagate error using e_prev = dE/dx = de/dx * e = trans(W) * e
	_prev->error() = _weights.t() * _error;
}

// Updates parameters (called after each batch)
void WeightLayer::updateParameters()
{
	if (_batchSize > 0)
		_learnRule->update(_weights, _gradients / (float)_batchSize);

	_gradients.clear();
	_batchSize = 0;
}

// Reads parameters from given stream
void WeightLayer::read(std::istream& stream)
{
	stream >> _weights;
}

// Writes parameters to given stream
void WeightLayer::write(std::ostream& stream) const
{
	stream << _weights;
}
