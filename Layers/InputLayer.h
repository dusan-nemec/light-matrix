#ifndef _INPUT_LAYER_H_
#define _INPUT_LAYER_H_

#include "NetLayer.h"

// Class InputLayer holds input.
class InputLayer : public NetLayer
{
public:
	// Constructs input with given size.
	InputLayer(int size) : NetLayer(size) {}

	// updates output from input
	virtual void processInput() { /* does nothing. */ }

	// updates error of the previous layer (call after each sample in batch).
	virtual void processError() { /* does nothing. */ }

	// Updates parameters (called after each batch).
	virtual void updateParameters() { /* no parameters to update. */ }

	// Appends this layer to the specified layer.
	virtual void appendTo(NetLayer* layer);
};

#endif // _INPUT_LAYER_H_