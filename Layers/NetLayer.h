#ifndef _NET_LAYER_H_
#define _NET_LAYER_H_

#include "../Matrix.h"
#include "../Learning/LearningRule.h"
#include <memory>
#include <iostream>
#include <string>

// Interface class for layers
class NetLayer
{
protected:
	NetLayer* _prev;
	NetLayer* _next;

	Matrix _output;
	Matrix _error;

public:
	// Creates new layer with given output size and learn algorithm.
	NetLayer(int size);

	// Destroys layer.
	virtual ~NetLayer();

	// Input of the layer (output of the previous layer).
	Matrix& input();
	const Matrix& input() const;

	// Output of the layer.
	const Matrix& output() const { return _output;  }
	Matrix& output() { return _output;  }

	// Output error of the layer.
	Matrix& error() { return _error; }
	const Matrix& error() const { return _error; }

	// Size of the layer.
	int size() const { return _output.rows(); }

	// Previous layer (or NULL if none).
	NetLayer* prevLayer() const { return _prev; }

	// Next layer (or NULL if none).
	NetLayer* nextLayer() const { return _next; }

	// Appends this layer to the specified layer.
    virtual void appendTo(NetLayer* layer);

	// Updates output from input. 
	// Note: Derived class MUST implement.
	virtual void processInput() = 0;

	// Updates error of the previous layer (call after each sample in batch). 
	// Note: Derived class MUST implement.
	virtual void processError() = 0;

	// Updates parameters (called after each batch).
	// Note: Derived class MUST implement.
	virtual void updateParameters() = 0;

	// Reads parameters from given stream.
	virtual void read(std::istream& stream) { /* does nothing. */ }

	// Writes parameters to given stream.
	virtual void write(std::ostream& stream) const { /* does nothing.*/ }
};

#endif