#include "Adam.h"

// Default constructor
Adam::Adam()
	: learningRate(0.001f), beta1(0.9f), beta2(0.999f), epsilon(1e-8f), _g1(), _g2(), _t(0) { }

// Updates parameters according to the learning rule.
// Note: if minibatch learning is used, [grads] contain sum gradient.
void Adam::update(Matrix& params, const Matrix& grads)
{
	if(params.size() != grads.size())
		throw std::invalid_argument("AdaMax: size of parameters and gradients has to be the same.");
	
	if (_g1.empty() || _g2.empty())
	{
		// first run, initialize
		_g1.resize(grads.size());
		_g2.resize(grads.size());
		_t = 0;
		_beta1_decayed = 1.0f;
		_beta2_decayed = 1.0f;
	}

	_t++;
	_beta1_decayed *= beta1;
	_beta2_decayed *= beta2;
	
	_g1 = beta1 * _g1 + (1 - beta1) * grads;
	_g2 = beta2 * _g2 + (1 - beta2) * Matrix::elemProd(grads, grads);
	
	Matrix norm1 = _g1 / (1 - _beta1_decayed);
	Matrix norm2 = _g2 / (1 - _beta2_decayed);
	params -= learningRate * Matrix::elemDiv(norm1, sqrt(norm2) + epsilon);
}
