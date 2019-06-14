#ifndef _BIAS_LAYER_H_
#define _BIAS_LAYER_H_

#include "NetLayer.h"
#include "../Learning/LearningRule.h"

// Implements bias layer
class BiasLayer : public NetLayer
{
private:
	Matrix _bias;
	Matrix _gradient;
	int _batchSize;
	
	LearningRule* _learnRule;

public:
	// Constructs new bias layer with given size.
	// Uses given learning rule and takes ownership of the given object.
	BiasLayer(int size, LearningRule* learnRule);

	// Destructor
	virtual ~BiasLayer();

	// updates output from input
	virtual void processInput();

	// updates error of the previous layer (call after each sample in batch).
	virtual void processError();

	// Updates parameters (called after each batch).
	virtual void updateParameters();

	// Returns bias of the layer
	const Matrix& bias() const { return _bias; }

	// Returns learning rule
	LearningRule* learningRule() const { return _learnRule; }

	// Reads parameters from given stream
	virtual void read(std::istream& stream);

	// Writes parameters to given stream
	virtual void write(std::ostream& stream) const;
};

#endif //_BIAS_LAYER_H_