//yop, jsuis Maxime :)
#include "stdafx.h"
#include "Neurons.h"

Neurons::Neurons(int modeTemp, int colonneTemp, int idTemp/*, std::vector<std::vector<Neurons>> *pointerLsTemp*/)
{
	//*pointerLs = *pointerLsTemp;
	mode = modeTemp;
	colonne = colonneTemp;
	id = idTemp;
}

void Neurons::makeLiaison(int nbNeuron)
{
	liaisons.push_back(nbNeuron);
}

void Neurons::breakLiaison(int nbNeuron)
{
	std::vector<int> replace;
	for (unsigned int i = 0; i < liaisons.size(); i++)
	{
		if (i != nbNeuron)
			replace.push_back(liaisons[i]);
	}
	liaisons.clear();
	liaisons = replace;
}

void Neurons::activate(std::vector<std::vector<Neurons>> *pointerLs2, void(*output)(int)) //0 = addition, 1 = multiplication, 2 = division, 3 = soustraction, 4 = &&, 5 = ||, 6 = !, 7 = CONST, 8 = MEM
{
	/*for (int m = 0; m < 9; m++) {
		int c = -1;
		int c2 = 0;
		for (int i = 0; i < liaisons.size(); i++)
		{
			if (liaisons[i] == m)
				if (c == -1)
				{
					c = i;
				}
				else
				{
					c2 = 1;
				}
		}
		if (c2) {
			std::vector<int>temp;
			temp.clear();
			for (int y = 0; y < liaisons.size(); y++) {
				if ( (y != c) && ( (*pointerLs2)[colonne + 1].size() > liaisons[y] ) )
					temp.push_back(liaisons[y]);
			}
			liaisons.swap(temp);
		}
	}*/
	std::vector<int> temp;
	for (int i = 0; i < liaisons.size(); i++)
		if ((*pointerLs2)[colonne + 1].size() > liaisons[i])
			temp.push_back(liaisons[i]);
	liaisons.clear();
	liaisons.swap(temp);
	int value = 0;
	switch (mode)
	{
	case 0: //+
		for (unsigned int i(0); i < inputs.size(); i++)
			value += inputs[i];
		inputs.clear();
		break;
	case 1: //x
		if (inputs.size() > 0)
			value = inputs[0];
		else
			value = 0;
		for (unsigned int i(1); i < inputs.size(); i++)
			value *= inputs[i];
		inputs.clear();
		break;
	case 2:// /
		if (inputs.size() > 0)
			value = inputs[0];
		else
			value = 0;
		for (unsigned int i(1); i < inputs.size(); i++)
			if (inputs[i] != 0)
				value /= inputs[i];
		inputs.clear();
		break;
	case 3://-
		if (inputs.size() > 0)
			value = inputs[0];
		else
			value = 0;
		for (unsigned int i(1); i < inputs.size(); i++)
			value -= inputs[i];
		inputs.clear();
		break;
	case 4: //&&
		if (inputs.size() > 0)
		{
			value = 1;
			for (unsigned int i(0); i < inputs.size() - 1; i++)
				if (inputs[i] != inputs[i + 1])
					value = 0;
			inputs.clear();
		}
		else
			value = 0;
		break;
	case 5: //||
		if (inputs.size() > 0)
		{
			for (unsigned int i(0); i < inputs.size(); i++)
				if (inputs[i] > 0)
					value = 1;
			inputs.clear();
		}
		else
			value = 0;
		break;
	case 6: //!
		if (inputs.size() > 0)
		{
			for (unsigned int i(0); i < inputs.size(); i++)
				value += inputs[i];
			if (value > 0)
				value = 0;
			else
				value = 1;
			inputs.clear();
		}
		else
			value = 1;
		break;
	case 7: //CONST
		if (inputs.size() > 0)
			value = inputs[0];
		else
			value = 0;
		break;
	case 8: //MEM
		if (inputs.size() > 0)
		{
			memory = inputs[inputs.size() - 1];
			inputs.clear();
			inputs.push_back(memory);
		}
		value = memory;
		break;
	default:
		break;
	}
	//std::cout << "pointerLs size: " << pointerLs2->size() << std::endl;
	if (value < -100000)
		value = 0;
	if (mode != 10)
		for (unsigned int i(0); i < liaisons.size(); i++)
			(*pointerLs2)[colonne + 1][liaisons[i]].inputs.push_back(value);
	else {
		for (unsigned int i(0); i < inputs.size(); i++)
			value += inputs[i];
		inputs.clear();
		(*output)(value);
	}
}

Neurons::~Neurons()
{
}
