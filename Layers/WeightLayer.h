#ifndef _WEIGHT_LAYER_H_
#define _WEIGHT_LAYER_H_


#include "NetLayer.h"
#include "../Learning/LearningRule.h"

// Simple dense weight matrix. Abstract class.
class WeightLayer : public NetLayer
{
protected:
	Matrix _weights;
	Matrix _gradients;
	int _batchSize;
	LearningRule* _learnRule;

public:
	// Constructs new weight layer with given output size and learning rule. Takes ownership of the learning rule.
	// Note: input size of the layer will be computed when appended to another layer.
	WeightLayer(int size, LearningRule* learnRule);

	// Destroys the object
	virtual ~WeightLayer();

	// Returns weight matrix
	const Matrix& weights() const { return _weights; }

	// Returns learn rule
	LearningRule* learningRule() const { return _learnRule; }

	// Appends this layer to the specified layer.
	virtual void appendTo(NetLayer* layer);

	// updates output from input
	virtual void processInput();

	// updates error of the previous layer and own gradient (call after each sample in batch).
	virtual void processError();

	// Updates parameters (called after each batch)
	virtual void updateParameters();

	// Reads parameters from given stream
	virtual void read(std::istream& stream);

	// Writes parameters to given stream
	virtual void write(std::ostream& stream) const;
};

#endif