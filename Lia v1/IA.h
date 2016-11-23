#pragma once

#include <vector>
#include "Neurons.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>

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

	int outInt = -1;
	int input1 = 0;
	//int nbOutput = 1; //une seul sortie pour play

	int score;
	std::vector<void (*)(int)> outputList;


	~IA();

	std::vector<std::vector<Neurons>> neuronsLs;
	int maxMode = 9;
	int newUpdate;
};

