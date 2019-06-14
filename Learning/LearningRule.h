#ifndef _LEARNING_RULE_H_
#define _LEARNING_RULE_H_

#include "../Matrix.h"
#include <iostream>

// Abstract interface for learning algorithms
class LearningRule
{
public:
	// Updates parameters according to the learning rule.
	// Note: if minibatch learning is used, [grads] contain average gradient.
	virtual void update(Matrix& params, const Matrix& grads)=0;
};

#endif // _LEARNING_RULE_H_