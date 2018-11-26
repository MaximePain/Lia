//yop, jsuis Maxime :)
#pragma once

#include <vector>
#include <iostream>
#include <functional>

class Neurons
{
public:
	Neurons(int modeTemp, int colonneTemp, int idTemp/*, std::vector<std::vector<Neurons>> *pointerLsTemp*/);
	void makeLiaison(int nbNeuron);
	void breakLiaison(int nbNeuron);

	void activate(std::vector<std::vector<Neurons>> *pointerLs2, void(*output)(int) = 0);
	void pushInput(int i);

	std::vector<int> liaisons;
	//std::vector<std::vector<Neurons>> *pointerLs = 0;

	std::vector<int> inputs;
	int mode;
	int colonne;
	int id;
	int memory;
	int input = 0;
	bool inputConst = false;
	bool inputX = false;

	~Neurons();
};

