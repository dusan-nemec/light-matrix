#ifndef _ADAM_H_
#define _ADAM_H_

#include "LearningRule.h"

// Implements Adam algorithm for stochastic optimization
class Adam : public LearningRule
{
private:
	Matrix  _g1; // filtered grad
	Matrix	_g2; // filtered grad^2
	unsigned _t; // time step
	float   _beta1_decayed; // decayed beta1 = beta1 ^ _t
	float 	_beta2_decayed; // decayed beta2 = beta2 ^ _t

public:
	// Default constructor.
	Adam();

	// Updates parameters according to the learning rule.
	// Note: if minibatch learning is used, [grads] contain average gradient.
	virtual void update(Matrix& params, const Matrix& grads);

	// Learning rate (small positive value). Default value is 0.001
	float learningRate;

	// Exponetial decay of the 1st momentum. Default value is 0.9
	float beta1;

	// Exponential decay of the 2nd momentum. Default value is 0.999
	float beta2;

	// Epsilon value preventing zero division. Default value is 1e-8
	float epsilon;
};

#endif // _ADAMAX_H_
