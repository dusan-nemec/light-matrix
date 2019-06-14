#ifndef _TANH_LAYER_H_
#define _TANH_LAYER_H_

#include "NetLayer.h"

// Implements hyperbolic tangent activation layer
class TanhLayer : public NetLayer
{
public:
	// Constructs new tanh layer with given [size].
	TanhLayer(int size) : NetLayer(size) { /* does nothing. */ }

	// updates output from input
	virtual void processInput();

	// updates error of the previous layer (call after each sample in batch).
	virtual void processError();

	// Updates parameters (called after each batch).
	virtual void updateParameters() { /* No parameters to update. */ }
};

#endif //_TANH_LAYER_H_