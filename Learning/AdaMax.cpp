#include "AdaMax.h"

// Default constructor
AdaMax::AdaMax()
	: learningRate(0.002f), beta1(0.9f), beta2(0.999f), _g1(), _g2(), _t(0), _beta1_decayed(1.0f) { }

// Updates parameters according to the learning rule.
// Note: if minibatch learning is used, [grads] contain sum gradient.
void AdaMax::update(Matrix& params, const Matrix& grads)
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
	}

	_t++;
	_beta1_decayed *= beta1;
	
	_g1 = beta1 * _g1 + (1 - beta1) * grads;
	_g2 = max(beta2 * _g2, abs(grads));
	
	float normRate = learningRate / (1 - _beta1_decayed);
	params -= normRate * Matrix::elemDiv(_g1, _g2);
}