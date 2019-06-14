#ifndef _SOFTPLUS_LAYER_H_
#define _SOFTPLUS_LAYER_H_

#include "NetLayer.h"

// Implements softplus activation layer (smooth approximation of ReLU).
class SoftplusLayer : public NetLayer
{
public:
	// Constructs new softplus layer with given [size].
	SoftplusLayer(int size) : NetLayer(size) { /* does nothing. */ }

	// updates output from input
	virtual void processInput();

	// updates error of the previous layer (call after each sample in batch).
	virtual void processError();

	// Updates parameters (called after each batch).
	virtual void updateParameters() { /* No parameters to update. */ }
};

#endif //_SOFTPLUS_LAYER_H_