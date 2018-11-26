#pragma once
#include "IA.h"

class Lia
{
public:
	Lia(std::string base = "0:0!0|0:0!0|1:0!0|");
	~Lia();

	void firstGen();
	void addOutput(void(*f)(int)) { network->addOutput(f); outputList.push_back(f); }
	void addInput(int *input) { network->addInput(input, inputLiaison); inputLiaison++; inputList.push_back(input); }
	void update() { genom[genom.size() - 1].update(); }
	bool newGenom();
	void newGeneration();

	void addScore(int nb = 1) { score[score.size() - 1] += nb; }
	void remScore(int nb = 1) { addScore(-nb); }
	void setGenomMax(int max) { genomMax = max; }
	std::string returnAdn() { return genom[genom.size() - 1].debug(); }
	std::string debug();

private:
	IA *network;
	int inputLiaison = 0;
	std::vector<IA> genom;
	std::vector<int> score;
	std::string neuronBase = "0:0!0|0:0!0|1:0!0|";

	std::vector<void(*)(int)> outputList;
	std::vector<int*> inputList;
	bool firstgen = true;
	int genomMax = 12;
	int nbGeneration = 1;
};

