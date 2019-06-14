#ifndef _RECTIFIER_LAYER_H_
#define _RECTIFIER_LAYER_H_

#include "NetLayer.h"

// Implements ReLU activation layer
class RectifierLayer : public NetLayer
{
public:
	// Constructs new ReLU layer with given [size].
	RectifierLayer(int size) : NetLayer(size) { /* does nothing. */ }

	// updates output from input
	virtual void processInput();

	// updates error of the previous layer (call after each sample in batch).
	virtual void processError();

	// Updates parameters (called after each batch).
	virtual void updateParameters() { /* No parameters to update. */ }
};

#endif //_RECTIFIER_LAYER_H_