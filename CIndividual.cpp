#include "CIndividual.h"
#include <random>
#include "CGeneticAlgorithm.h"
#include <iostream>
using namespace std;


CIndividual::CIndividual(CKnapsackProblem* cKnapsack, double dMutationProb)
{
	c_knapsack = cKnapsack;
	i_count_gen = c_knapsack->iGetItemsCount();
	d_mutation_prob = dMutationProb;
	d_fitness = 0;

	pi_genotype = new int[i_count_gen];
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = iGenerateInteger(0, 1);
	}
	vSetFitness();

	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

CIndividual::CIndividual(CKnapsackProblem* cKnapsack, double dMutationProb, int* piTable)
{
	c_knapsack = cKnapsack;
	i_count_gen = c_knapsack->iGetItemsCount();
	d_mutation_prob = dMutationProb;
	d_fitness = 0;

	pi_genotype = new int[i_count_gen];
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = piTable[i];
	}
	vSetFitness();

	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

CIndividual::~CIndividual()
{
	delete[] pi_genotype;
}

void CIndividual::vMutation(double dMutationProb)
{
	for(int i = 0; i < i_count_gen; i++)
	{
		double d_number = dGenerateDouble(0.0, 1.0);
		if(!(d_number>dMutationProb))
		{
			pi_genotype[i] = (pi_genotype[i] + 1) % 2;
		}
	}
	d_fitness = 0;
	vSetFitness();
	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);

}

std::vector<CIndividual*> CIndividual::vCrossing(CIndividual* cSecondParent)
{
	vector<CIndividual*> v_children(0);
	int i_index_part = iGenerateInteger(1, i_count_gen - 1);
	int ** pi_table = new int*[2];
	pi_table[0] = new int[i_count_gen];
	pi_table[1] = new int[i_count_gen];
	for(int j = 0; j<i_count_gen; j++)
	{
		if (j < i_index_part) 
		{
			pi_table[0][j] = iGetGen(j);
			pi_table[1][j] = cSecondParent->iGetGen(j);
		}else
		{
			pi_table[0][j] = cSecondParent->iGetGen(j);
			pi_table[1][j] = iGetGen(j);
		}
	}
	v_children.push_back(new CIndividual(c_knapsack, d_mutation_prob, pi_table[0]));
	v_children.push_back(new CIndividual(c_knapsack, d_mutation_prob, pi_table[1]));

	for(int i = 0; i < 2; i++)
	{
		delete[] pi_table[i];
	}
	delete[] pi_table;
	return v_children;
}

CIndividual* CIndividual::operator+(CIndividual* pcOther)
{

	int i_index_part = iGenerateInteger(1, i_count_gen - 1);
	int ** pi_table = new int*[2];
	pi_table[0] = new int[i_count_gen];
	pi_table[1] = new int[i_count_gen];
	for (int j = 0; j < i_count_gen; j++)
	{
		if (j < i_index_part)
		{
			pi_table[0][j] = iGetGen(j);
			pi_table[1][j] = pcOther->iGetGen(j);
		}
		else
		{
			pi_table[0][j] = pcOther->iGetGen(j);
			pi_table[1][j] = iGetGen(j);
		}
	}
	CIndividual* c_first = new CIndividual(c_knapsack, d_mutation_prob, pi_table[0]);
	CIndividual* c_sec = new CIndividual(c_knapsack, d_mutation_prob, pi_table[1]);

	CIndividual* child;

	if (c_first->dGetFitness() > c_sec->dGetFitness())
	{
		child = c_first;
		delete c_sec;
	}
	else{
		child = c_sec;
		delete c_first;
	}

	for (int i = 0; i < 2; i++)
	{
		delete[] pi_table[i];
	}
	delete[] pi_table;
	return  child;
}

void CIndividual::operator++(int)
{
	for (int i = 0; i < i_count_gen; i++)
	{
		double d_number = dGenerateDouble(0.0, 1.0);
		if (!(d_number > d_mutation_prob))
		{
			pi_genotype[i] = (pi_genotype[i] + 1) % 2;
		}
	}
	d_fitness = 0;
	vSetFitness();
	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

double CIndividual::dGetFitness()
{
	return d_fitness;
}

int CIndividual::iGetGen(int iIndex)
{
	return pi_genotype[iIndex];
}

double CIndividual::dGetValueGen()
{
	return d_value_gen;
}

void CIndividual::vDisplay()
{
	cout << "Fitness:	" << d_fitness <<"	Size:		" << d_size_gen<< "	[";
	for (int j = 0; j < i_count_gen - 1; j++)
	{
		cout << pi_genotype[j] << ",";
	}
	cout << pi_genotype[i_count_gen - 1] << "]" << endl;
}

void CIndividual::vSetFitness()
{
	double d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);

	if (d_size_gen <= c_knapsack->dGetKnapsackSize()) d_fitness = c_knapsack->dGetValueFromGen(pi_genotype);
}

int CIndividual::iGenerateInteger(int iFrom, int iTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(iFrom, iTo);

	return dis(gen);
}

double CIndividual::dGenerateDouble(double dFrom, double dTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(dFrom, dTo);

	return dis(gen);
}

