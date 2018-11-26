#include "stdafx.h"
#include "Lia.h"

Lia::Lia(std::string base)
{
	network = new IA(base);
}

void Lia::firstGen() {
	if (firstgen) {
		newGenom();
		firstgen = false;
	}
}

bool Lia::newGenom() {
	if (genom.size() < genomMax) {
		IA *tempIa = new IA(network->returnADN());
		for (int i = 0; i < outputList.size(); i++)
			tempIa->addOutput(outputList[i]);
		for (int i = 0; i < inputList.size(); i++)
			tempIa->addInput(inputList[i], i);
		tempIa->mutate();

		genom.push_back(IA(tempIa->returnADN()));
		for (int i = 0; i < outputList.size(); i++)
			genom[genom.size() - 1].addOutput(outputList[i]);
		for (int i = 0; i < inputList.size(); i++)
			genom[genom.size() - 1].addInput(inputList[i], i);
		score.push_back(0);
		delete tempIa;
		tempIa = 0;
		return true;
	}
	else
		return false;
}

void Lia::newGeneration() {
	int temp, scoreMax1, scoreMax2;
	temp = -1;
	for (int i = 0; i < score.size(); i++)
	{
		if (temp < score[i])
		{
			temp = score[i];
			scoreMax1 = i;
		}
	}
	temp = -1;
	for (int i = 0; i < score.size(); i++)
	{
		if (temp < score[i] && i != scoreMax1)
		{
			temp = score[i];
			scoreMax2 = i;
		}
	}
	delete network;
	network = 0;

	network = new IA(IA::fusion(genom[scoreMax1].returnADN(), genom[scoreMax2].returnADN()));
	genom.clear();
	score.clear();
	nbGeneration++;
	firstgen = true;
}

std::string Lia::debug() {
	return genom[genom.size() - 1].returnADN();
}

Lia::~Lia()
{
}
