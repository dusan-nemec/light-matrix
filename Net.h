#ifndef _NET_H_
#define _NET_H_

#include "Layers/NetLayer.h"
#include "Layers/InputLayer.h"
#include "Layers/WeightLayer.h"
#include "Layers/TanhLayer.h"
#include "Layers/RectifierLayer.h"
#include "Layers/SoftplusLayer.h"
#include "Layers/BiasLayer.h"

class Net
{
protected:
	std::vector<NetLayer*> _layers;

public:
	// Creates new empty network
	Net();

	// Destroys network and all its layers
	~Net();

	// Adds new layer to the end of the network. Takes ownership of given layer.
	void addLayer(NetLayer* layer);

	// Clears all layers
	void clear() { _layers.clear(); }

	// Returns vector of layers.
	const std::vector<NetLayer*>& layers() const { return _layers; }

	// Returns output of the last layer. Call only if network has layers.
	const Matrix& output() const { return _layers.back()->output(); }

	// Runs whole network forward (from given input to output).
	void processInput(const Matrix& in);

	// Processes error (from output to input). Call after each sample in the batch.
	void processError(const Matrix& err);

	// Updates parameters of all layers (from output to input). Call after each batch.
	void updateParameters();

	// Loads network parameters from given file. Structure has to be set first.
	void loadFromFile(const char* filename);

	// Saves network parameters to given file.
	void saveToFile(const char* filename) const;
};

#endif 
