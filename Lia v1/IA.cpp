#include "stdafx.h"
#include "IA.h"

int IA::numFindStr(std::string str0, std::string strF)
{
	int ret = 0;
	int nbChar = 0;

	for (unsigned int i = 0; i < str0.size(); i++)
	{
		if (str0[i] == strF[nbChar])
		{
			nbChar++;
			if (nbChar == strF.size())
			{
				ret++;
				nbChar = 0;
			}
		}
		else
			nbChar = 0;
	}

	return ret;
}

IA::IA(std::string params) //std::string neuronBase = "0:0!0|0:0!0|0:0!0|0:0!0|0:0!0|1:10!0|";
{
	bool end = false;
	unsigned int nbChar = 0;
	int nbCol;
	std::vector<int> nbColVec;
	bool littleExist = false;
	int nbNeuron = -1;
	int mode = 0; //0 = col, 1 = nbN, 2 = liaison
	int modeNeuron;
	int liaisonNum;
	std::string msg = "";
	std::vector<Neurons> n0;
	bool first = true;
	std::vector<bool> rajout;
	while (!end)
	{
		switch (mode)
		{
		case 0:
			while (params[nbChar] != ':')
			{
				msg += params[nbChar];
				nbChar++;
			}
			nbCol = atoi(msg.c_str());
			nbChar++;
			/*for (unsigned int c(0); c < nbColVec.size(); c++)
				if (nbCol == c)
					littleExist = true;
			if (!littleExist) {
				neuronsLs.push_back(n0);
				nbColVec.push_back(0);
			}
			else
				littleExist = false;*/

			while (nbColVec.size() <= nbCol)
			{
				rajout.push_back(0);
				neuronsLs.push_back(n0);
				nbColVec.push_back(0);
			}
			msg = "";
			mode = 1;
			break;
		case 1:
			while (params[nbChar] != '!')
			{
				msg += params[nbChar];
				nbChar++;
			}
			nbChar++;
			modeNeuron = atoi(msg.c_str());
			msg = "";
			mode = 2;
			neuronsLs[nbCol].push_back(Neurons(modeNeuron, nbCol, nbColVec[nbCol]));
			/*neuronsLs[nbCol][neuronsLs[nbCol].size() - 1].pointerLs = &neuronsLs;
			std::cout << "pointerLs size: " << neuronsLs[nbCol][neuronsLs[nbCol].size() - 1].pointerLs->size() << std::endl;
			if (modeNeuron == 10)
				neuronsLs[nbCol][nbColVec[nbCol]].outIntP = &outInt;*/
			nbColVec[nbCol]++;
			break;
		case 2:
			std::stringstream ss;
			ss.str("");
			ss.clear();
			bool hasLiaison = false;
			while (params[nbChar] != '|')
			{
				hasLiaison = true;
				while (params[nbChar] != ',' && params[nbChar] != '|')
				{
					msg += params[nbChar];
					nbChar++;
				}

				liaisonNum = atoi(msg.c_str());
				ss.str("");
				ss.clear();
				ss << '|';
				ss << (nbCol + 1);
				ss << ':';
				if (params[nbChar] != '|')
					nbChar++;
				if (numFindStr(params, ss.str()) == 0 && modeNeuron != 10 && !rajout[nbCol]) //rectification si colonne a disparue (on sait jamais)
				{
					rajout[nbCol] = true;
					rajout.push_back(0);
					neuronsLs.push_back(n0);
					nbColVec.push_back(0);
					neuronsLs[nbCol + 1].push_back(Neurons(0, nbCol + 1, nbColVec[nbCol + 1]));
					nbColVec[nbCol + 1]++;
				}
				if (liaisonNum != 0) {
					if (numFindStr(params, ss.str()) > liaisonNum + 1) //rectification si neuronne a disparue en ajoutant liasion
						neuronsLs[nbCol][nbColVec[nbCol] - 1].makeLiaison(liaisonNum);
				}
				else
					if (numFindStr(params, ss.str()) > liaisonNum)
						neuronsLs[nbCol][nbColVec[nbCol] - 1].makeLiaison(liaisonNum);
				msg = "";
			}
			if (!hasLiaison)
				neuronsLs[nbCol][nbColVec[nbCol] - 1].makeLiaison(0);
			nbChar++;
			if (params.size() > nbChar)
				mode = 0;
			else
				end = true;
			break;
		}
	}

	//std::cout << "neu0: " << neuronsLs[neuronsLs.size() - 2][neuronsLs[neuronsLs.size() - 1].size()].mode << std::endl;

	if (rajout[neuronsLs.size() - 2])
	{
		std::cout << "multi sortie error" << std::endl;
		neuronsLs.pop_back();
		for (unsigned int i = 0; i < neuronsLs[neuronsLs.size() - 1].size() + 1; i++)
		{
			neuronsLs[neuronsLs.size() - 1].pop_back();
		}
		neuronsLs[nbCol].push_back(Neurons(10, (neuronsLs[neuronsLs.size() - 1].size() - 1), 0));
	}
	neuronsLs[neuronsLs.size() - 1][neuronsLs[neuronsLs.size() - 1].size() - 1].makeLiaison(0);
	//std::cout << "adn: " << returnADN() << std::endl;
}

void IA::update()
{
	//std::cout << "neuronLs size: " << neuronsLs.size() << std::endl;
	//std::cout << "pointerLs size: " << neuronsLs[0][0].pointerLs->size() << std::endl;
	//std::cout << "adn: " << returnADN() << std::endl;
	newUpdate = 0;

	for (int &i : inputListLiaison)
	{
		int* inputPointer = inputList[i];
		neuronsLs[0][inputListLiaison[i]].inputs.push_back(*inputPointer);
	}

	for (unsigned int i(0); i < neuronsLs.size(); i++)
		for (unsigned int y(0); y < neuronsLs[i].size(); y++)
		{
			if(neuronsLs[i][y].mode != 10)
				neuronsLs[i][y].activate(&neuronsLs);
			else
			{
				neuronsLs[i][y].activate(&neuronsLs, outputList[newUpdate]);
				newUpdate++;
			}
		}
}

std::string IA::returnADN()
{
	std::string msg = "";
	std::stringstream ss;
	for (unsigned int i(0); i < neuronsLs.size(); i++)
	{
		for (unsigned int y(0); y < neuronsLs[i].size(); y++)
		{
			ss << i;
			ss << ':';
			ss << neuronsLs[i][y].mode;
			ss << '!';
			for (unsigned int z(0); z < neuronsLs[i][y].liaisons.size(); z++)
			{
				ss << neuronsLs[i][y].liaisons[z];
				if ((z + 1) < neuronsLs[i][y].liaisons.size())
					ss << ',';
			}
			ss << '|';
		}
	}
	msg = ss.str();
	return msg;
}

bool IA::mutate()
{
	bool ret = false;
	for (unsigned int i(0); i < neuronsLs.size() - 1; i++)
	{
		for (unsigned int y(0); y < neuronsLs[i].size(); y++)
		{
			if ((rand() % 100) == 1)
			{
				neuronsLs[i][y].mode = rand() % maxMode;
				if ((rand() % 2) == 1) //liaison
				{
					if ((rand() % 2) == 1) //make liaison
					{
						if (neuronsLs[i][y].liaisons.size() < neuronsLs[i + 1].size())
						{
							int varRandLiaison = 0;
							bool exist = false;
							do {
								varRandLiaison = rand() % neuronsLs[i + 1].size();
								for (unsigned int z = 0; z < neuronsLs[i][y].liaisons.size(); z++)
									if (varRandLiaison == neuronsLs[i][y].liaisons[z])
										exist = true;
									else
										exist = false;
							} while (exist);
							neuronsLs[i][y].makeLiaison(varRandLiaison);
							ret = true;
						}
					}
					else //break liaison
					{
						if (neuronsLs[i][y].liaisons.size() > 1)
						{
							neuronsLs[i][y].breakLiaison(rand() % neuronsLs[i][y].liaisons.size());
							ret = true;
						}

					}
				}
				if ((rand() % 10) == 1 || 1 == 1) //changement mode
				{
					neuronsLs[i][y].mode = rand() % maxMode;
					ret = true;
				}
			}
		}
		if ((rand() % 2000) == 1) //addColonne (+add one neuron)
		{
			std::vector<std::vector<Neurons>> replace;
			std::vector<Neurons> replaceChild;
			for (unsigned int i2(0); i2 < neuronsLs.size(); i2++)
			{
				replace.push_back(neuronsLs[i2]);
				if (i2 == i)
				{
					replace.push_back(replaceChild);
					replace[i2 + 1].push_back(Neurons(rand() % maxMode, i2 + 1, 0/*, &neuronsLs*/));
					replace[i2 + 1][0].makeLiaison(0);
				}
			}
			neuronsLs.clear();
			neuronsLs = replace;
			ret = true;
		}
		if ((rand() % 1000) == 1) //addNeuron
		{
			neuronsLs[i].push_back(Neurons(rand() % maxMode, i, neuronsLs[i].size()/*, &neuronsLs*/));
			neuronsLs[i][neuronsLs[i].size() - 1].makeLiaison(0);
			ret = true;
		}
	}
	return ret;
}

void IA::output(int out)
{
	//std::cout << "output: " << outInt << std::endl;
	outputList[newUpdate](out);
}

std::string IA::fusion(std::string genom1, std::string genom2) //std::string neuronBase = "0:0!0|0:0!0|0:0!0|0:0!0|0:0!0|1:10!0|";
{
	std::string result = "";
	std::string extract1 = "";
	std::string extract2 = "";
	int nbChar1 = 0;
	int nbChar2 = 0;

	if (genom2.size() > genom1.size()) //genom1 doit etre la plus grande
		genom2.swap(genom1);

	int nbD10 = numFindStr(genom1, ":10");
	int nbD10Found = 0;

	while (1)
	{
		while (genom1[nbChar1] != '|')
		{
			extract1 += genom1[nbChar1];
			nbChar1++;
		}
		extract1 += '|';
		nbChar1++;
		if (nbChar2 + 1 < genom2.size())
		{
			while (genom2[nbChar2] != '|')
			{
				extract2 += genom2[nbChar2];
				nbChar2++;
			}
			nbChar2++;
			extract2 += '|';

		}
		else
			extract2 = extract1;
		if (extract1.find(":10") != std::string::npos)
		{
			nbD10Found++;
			result += extract1;
			if(nbD10Found >= nbD10)
				break;
		}
		if (extract1.find(":10") == std::string::npos && extract2.find(":10") == std::string::npos)
		{
			if (rand() % 2 == 0)
				result += extract1;
			else
				result += extract2;
		}
		if (extract2.find(":10") != std::string::npos && extract1.find(":10") == std::string::npos)
		{
			result += extract1;
		}
		extract1 = "";
		extract2 = "";


		if (nbChar1 + 1 >= genom1.size())
			break;
	}
	//std::cout << "result: " << result << std::endl;
	return result;
}

void IA::addOutput( void (*f)(int) )
{
	outputList.push_back(f);
}

void IA::addInput(int *input, int liaison)
{
	inputList.push_back(input);
	inputListLiaison.push_back(liaison);
}

IA::~IA()
{
}
