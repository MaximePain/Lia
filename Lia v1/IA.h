#pragma once

#include "Game.h"
#include <vector>
#include "Neurons.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include "Game.h"

class IA
{
public:
	IA(std::string params);
	void update();

	std::string returnADN();
	bool mutate();

	void output();
	int numFindStr(std::string str0, std::string strF);


	int outInt = -1;
	int input1 = 0;
	//int nbOutput = 1; //une seul sortie pour play

	Game *gameP;
	int score;

	std::string fusion(std::string genom1, std::string genom2);

	~IA();

	std::vector<std::vector<Neurons>> neuronsLs;
	int maxMode = 9;
};

