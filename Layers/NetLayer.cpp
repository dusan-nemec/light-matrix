#include "NetLayer.h"


NetLayer::NetLayer(int size)
	: _prev(), _next(), _output(size), _error(size) { }


NetLayer::~NetLayer()
{
	// Disconnect from chain
	if (_prev)
		_prev->_next = _next;

	if (_next)
		_next->_prev = _prev;
}


// Input of the layer (output of the previous layer).
Matrix& NetLayer::input()
{
	if (_prev)
		return _prev->output();
	else
		return _output; // input layer
}

const Matrix& NetLayer::input() const
{
	if (_prev)
		return _prev->output();
	else
		return _output; // input layer
}

// Appends this layer to the specified layer.
void NetLayer::appendTo(NetLayer* layer)
{
	if (!layer)
		throw std::invalid_argument("NetLayer::appendTo: argument cannot be null.");

	if (_prev || _next)
		throw std::runtime_error("NetLayer::appendTo: layer already bound with an another layer.");

	_prev = layer;
	_prev->_next = this;
}