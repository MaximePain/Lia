#pragma once

#include <vector>
#include <iostream>

class Neurons
{
public:
	Neurons(int modeTemp, int colonneTemp, int idTemp/*, std::vector<std::vector<Neurons>> *pointerLsTemp*/);
	void makeLiaison(int nbNeuron);
	void breakLiaison(int nbNeuron);

	void activate(std::vector<std::vector<Neurons>> *pointerLs2, int *outIntP);

	std::vector<int> liaisons;
	//std::vector<std::vector<Neurons>> *pointerLs = 0;

	std::vector<int> inputs;
	int mode;
	int colonne;
	int id;
	int memory;

	~Neurons();
};

