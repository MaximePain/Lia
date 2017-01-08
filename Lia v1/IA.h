//yop, jsuis Maxime :)
#pragma once

#include <vector>
#include "Neurons.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <functional>

class IA
{
public:
	IA(std::string params);
	void update();

	std::string returnADN();
	bool mutate();

	void output(int out);
	int numFindStr(std::string str0, std::string strF);
	std::string fusion(std::string genom1, std::string genom2);

	void addOutput( void (*f)(int) );
	void addInput(int *input, int liaison);

	int outInt = -1;

	//int nbOutput = 1; //une seul sortie pour play

	int score;
	std::vector<void (*)(int)> outputList;
	

	~IA();

	std::vector<std::vector<Neurons>> neuronsLs;
	int maxMode = 9;
	std::vector<int*> inputList;
	std::vector<int> inputListLiaison;
	int newUpdate;
	bool alreadyOutAdd = false;
};

