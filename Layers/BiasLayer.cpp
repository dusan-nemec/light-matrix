#include "BiasLayer.h"

// Constructs new bias layer with given size.
// Uses given learning rule and takes ownership of the given object.
BiasLayer::BiasLayer(int size, LearningRule* learnRule)
	: NetLayer(size), _bias(size,1), _gradient(size, 1), _batchSize(0), _learnRule(learnRule) 
{
	_bias.rand(-1.0f, 1.0f);
	_gradient.clear();
}

// Destructor
BiasLayer::~BiasLayer()
{
	delete _learnRule;
}

// updates output from input
void BiasLayer::processInput()
{
	if (!_prev)
		throw std::runtime_error("BiasLayer: Missing previous layer.");

	// Add bias
	_output = _prev->output() + _bias;
}

// updates error of the previous layer (call after each sample in batch).
void BiasLayer::processError()
{
	if (!_prev)
		throw std::runtime_error("WeightLayer: Missing previous layer.");

	// Compute and accumulate gradient = dE/db = dE/dy * dy/db = err
	_gradient += _error;
	_batchSize++;

	// Backpropagate error err_prev = dE/dx = dE/dy * dy/dx = err
	_prev->error() = _error;
}

// Updates parameters (called after each batch).
void BiasLayer::updateParameters()
{
	if (_batchSize > 0)
		_learnRule->update(_bias, _gradient / (float)_batchSize);

	_gradient.clear();
	_batchSize = 0;
}


// Reads parameters from given stream
void BiasLayer::read(std::istream& stream)
{
	stream >> _bias;
}

// Writes parameters to given stream
void BiasLayer::write(std::ostream& stream) const
{
	stream << _bias;
}