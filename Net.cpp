#include "Net.h"
#include <fstream>

// Creates new empty network
Net::Net()
	: _layers() {}

// Destroys network and all its layers
Net::~Net()
{
	for (unsigned i = 0; i < _layers.size(); i++)
		delete _layers[i];
}


// Adds new layer to the end of the network. Takes ownership of given layer.
void Net::addLayer(NetLayer* layer)
{
	if (_layers.size() > 0)
		layer->appendTo(_layers.back());
	
	_layers.push_back(layer);
}

// Runs whole network forward (from given input to output).
void Net::processInput(const Matrix& in)
{
	if (_layers.empty()) return; // nothing to do

	// set input first
	_layers[0]->input() = in;

	// Iterate through chain in forward direction
	for (unsigned i = 0; i < _layers.size(); i++)
		_layers[i]->processInput();
}

// Processes error (from output to input). Call after each sample in the batch.
void Net::processError(const Matrix& err)
{
	if (_layers.empty()) return; // nothing to do

	// set output error
	_layers.back()->error() = err;

	// Iterate reversly through chain
	for (int i = (int)_layers.size() - 1; i >= 0; i--)
		_layers[i]->processError();
}

// Updates parameters of all layers (from output to input). Call after each batch.
void Net::updateParameters()
{
	if (_layers.empty()) return; // nothing to do

	// Iterate reversly through chain
	for (int i = (int)_layers.size() - 1; i >= 0; i--)
		_layers[i]->updateParameters();
}

// Loads network parameters from given file. Structure has to be set first.
void Net::loadFromFile(const char* filename)
{
	std::ifstream file(filename);

	if (!file.is_open()) return;

	for (unsigned i = 0; i < _layers.size(); i++)
		_layers[i]->read(file);

	file.close();
}

// Saves network to given file.
void Net::saveToFile(const char* filename) const
{
	std::ofstream file(filename);

	for (unsigned i = 0; i < _layers.size(); i++)
		_layers[i]->write(file);

	file.close();
}
