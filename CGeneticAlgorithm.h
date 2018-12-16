#pragma once
#include <random>
#include <iostream>
#include <chrono>
#include "CKnapsackProblem.h"
#define DEFAULT_COUNT_GEN 3
#define DEFAULT_MUTATION_VALUE 1

template<class T>
class CIndividual
{
public:
	CIndividual(CKnapsackProblem<T>* cKnapsack, double dMutationProb);
	CIndividual(CKnapsackProblem<T>* cKnapsack, double dMutationProb, T * piTable);
	void vGenerateGens();
	~CIndividual();


	CIndividual* operator+(CIndividual * pcOther);
	void operator++(int);
	void vMutationHelper();


	double dGetFitness();
	T iGetGen(int iIndex);
	double dGetValueGen();

	void vDisplay();
private:
	void vSetFitness();
	int iGenerateInteger(int iFrom, int iTo);
	double dGenerateDouble(double dFrom, double dTo);

	T * pi_genotype;
	int i_count_gen;
	double d_fitness;
	double d_value_gen;
	double d_size_gen;
	double d_mutation_prob;

	CKnapsackProblem<T>* c_knapsack;
};

template<class T>
class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm()
	{
		i_population_size = 0;
		d_mutation_prob = 0;
		d_cross_prob = 0;
		pc_knapsack_problem = NULL;
		ppc_tab_population = NULL;
		pc_best_individual = NULL;
	}
	~CGeneticAlgorithm()
{
	for (int i = 0; i<i_population_size; i++)
	{
		if(ppc_tab_population[i]!=pc_best_individual)
		delete ppc_tab_population[i];
	}

	delete[] ppc_tab_population;
	delete pc_best_individual;
}

	bool bInitialObject(int iPopulationSize, double dMutationProb, double dCrossProb, CKnapsackProblem<T> * cKnapsackProblem);
	void vStartAlgorithm(double dTime);
	void vGenerateNewPopulation();
	double dGetMutationProb();
	
private:
	bool bMatchBestIndividual(CIndividual<T>* cToMatch);
	int iGenerateInteger(int iFrom, int iTo);
	double dGenerateDouble(double dFrom, double dTo);

	int i_population_size;
	double d_mutation_prob;
	double d_cross_prob;

	CIndividual<T> ** ppc_tab_population;
	CIndividual<T> * pc_best_individual;
	CKnapsackProblem<T> * pc_knapsack_problem;
};


/*@@@@@@@@@@@@@			GENETIC	ALGORITHM			@@@@@@@@@@@@@*/


template<class T>
bool CGeneticAlgorithm<T>::bInitialObject(int iPopulationSize, double dMutationProb, double dCrossProb,
	CKnapsackProblem<T>* cKnapsackProblem)
{
	if (dMutationProb >= 0
		&& dMutationProb <= 1
		&& dCrossProb >= 0
		&& dCrossProb <= 1
		&& iPopulationSize > 1)
	{
		i_population_size = iPopulationSize;
		d_mutation_prob = dMutationProb;
		d_cross_prob = dCrossProb;
		pc_knapsack_problem = cKnapsackProblem;
		ppc_tab_population = new CIndividual<T>*[i_population_size];
		for (int i = 0; i < i_population_size; i++)
		{
			ppc_tab_population[i] = new CIndividual<T>(pc_knapsack_problem, d_mutation_prob);
			//ppc_tab_population[i]->vAddAlg(this);
		}

		pc_best_individual = ppc_tab_population[0];

		for (int i = 1; i < i_population_size;i++)
		{
			if (ppc_tab_population[i]->dGetFitness() > pc_best_individual->dGetFitness())
			{
				pc_best_individual = ppc_tab_population[i];
			}
		}//for (int i = 1; i < i_population_size;i++)

		return true;
	}//if(dMutationProb >= 0 && dMutationProb <= 1 && dCrossProb >= 0 && dCrossProb <= 1 && iPopulationSize > 1)
	return false;
}

template<class T>
void CGeneticAlgorithm<T>::vStartAlgorithm(double dTime)
{
	int i_iter_population = 0;
	clock_t start = clock();
	while (((double)clock() - start) / CLOCKS_PER_SEC < dTime)
	{
		vGenerateNewPopulation();
		i_iter_population++;
	}
	std::cout << "###	LAST POP	###" << std::endl;
	for (int i = 0; i < i_population_size; i++)
	{
		ppc_tab_population[i]->vDisplay();
	}

	std::cout << i_iter_population << "THE BEST IS: " << std::endl; pc_best_individual->vDisplay();
}//CGeneticAlgorithm<T>::vGeneratePopulation(int iIter)

template<class T>
void CGeneticAlgorithm<T>::vGenerateNewPopulation()
{
	std::cout << "###	POP	###" << std::endl;
	for (int i = 0; i < i_population_size; i++)
	{
		ppc_tab_population[i]->vDisplay();
	}
	int i_random_number1;
	int i_random_number2;
	int i_children_count = 0;

	CIndividual<T> ** pc_new_population = new CIndividual<T>*[i_population_size];

	while (i_children_count < i_population_size)
	{
		int *pi_parents = new int[2];

		for (int i = 0; i < 2; i++)
		{
			i_random_number1 = iGenerateInteger(0, i_population_size - 1);
			i_random_number2 = i_random_number1;

			while (i_random_number2 == i_random_number1)
			{
				i_random_number2 = iGenerateInteger(0, i_population_size - 1);
			}//while (i_random_number2 == i_random_number1)

			if (ppc_tab_population[i_random_number1]->dGetFitness() >= ppc_tab_population[i_random_number2]->dGetFitness())
			{
				pi_parents[i] = i_random_number1;
			}
			else
			{
				pi_parents[i] = i_random_number2;
			} // ELSE ppc_tab_population[i_random_number1]->dGetFitness() >= ppc_tab_population[i_random_number2]->dGetFitness())
		}//	for(int i = 0; i < 2; i++)

		double d_crossing = dGenerateDouble(0, 1);

		if (d_crossing <= d_cross_prob)
		{
			CIndividual<T>* c_child = (*ppc_tab_population[pi_parents[0]]) + ppc_tab_population[pi_parents[1]];
			//CIndividual & rc_child = *c_child;
			//rc_child++;
			(*c_child)++;
			pc_new_population[i_children_count++] = c_child;

		}//if (d_crossing <= d_cross_prob)

		delete[] pi_parents;
	}//while(i_children_count >= i_population_size)

	//delete old population without the best individual
	for (int i = 0; i < i_population_size; i++)
	{
		if (ppc_tab_population[i] != pc_best_individual)
			delete ppc_tab_population[i];
	}
	delete[] ppc_tab_population;

	ppc_tab_population = pc_new_population;

	//check new population for new the best individual
	int i_index_best = -1;
	double d_fitness_best = -1;
	for (int i = 0; i < i_population_size;i++)
	{
		if (ppc_tab_population[i]->dGetFitness() > d_fitness_best) {
			i_index_best = i;
			d_fitness_best = ppc_tab_population[i]->dGetFitness();
		}
	}//for (int i = 1; i < i_population_size;i++)

	bMatchBestIndividual(ppc_tab_population[i_index_best]);
}

template<class T>
double CGeneticAlgorithm<T>::dGetMutationProb()
{
	return d_mutation_prob;
}

template<class T>
bool CGeneticAlgorithm<T>::bMatchBestIndividual(CIndividual<T>* cToMatch)
{
	if (cToMatch->dGetFitness() > pc_best_individual->dGetFitness())
	{
		delete pc_best_individual;
		pc_best_individual = cToMatch;
		return true;
	}
	return false;
}

template<class T>
int CGeneticAlgorithm<T>::iGenerateInteger(int iFrom, int iTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> dis(iFrom, iTo);

	return dis(gen);
}

template<class T>
double CGeneticAlgorithm<T>::dGenerateDouble(double dFrom, double dTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(dFrom, dTo);

	return dis(gen);
}



/*@@@@@@@@@@@@@				INDIVIDUAL				@@@@@@@@@@@@@*/


template<class T>
CIndividual<T>::CIndividual(CKnapsackProblem<T>* cKnapsack, double dMutationProb)
{
	c_knapsack = cKnapsack;
	i_count_gen = c_knapsack->iGetItemsCount();
	d_mutation_prob = dMutationProb;
	d_fitness = 0;

	pi_genotype = new T[i_count_gen];
	vGenerateGens();
	vSetFitness();

	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

template<class T>
CIndividual<T>::CIndividual(CKnapsackProblem<T>* cKnapsack, double dMutationProb, T* piTable)
{
	c_knapsack = cKnapsack;
	i_count_gen = c_knapsack->iGetItemsCount();
	d_mutation_prob = dMutationProb;
	d_fitness = 0;

	pi_genotype = new T[i_count_gen];
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = piTable[i];
	}
	vSetFitness();

	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

void CIndividual<int>::vGenerateGens()
{
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = iGenerateInteger(0, DEFAULT_COUNT_GEN);
	}
}

void CIndividual<double>::vGenerateGens()
{
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = dGenerateDouble(0, DEFAULT_COUNT_GEN);
	}
}

void CIndividual<bool>::vGenerateGens()
{
	for (int i = 0; i < i_count_gen; i++)
	{
		pi_genotype[i] = iGenerateInteger(0, 1);
	}
}

template<class T>
CIndividual<T>::~CIndividual()
{
	delete[] pi_genotype;
}

template<class T>
CIndividual<T>* CIndividual<T>::operator+(CIndividual* pcOther)
{

	int i_index_part = iGenerateInteger(1, i_count_gen - 1);
	T ** pi_table = new T*[2];
	pi_table[0] = new T[i_count_gen];
	pi_table[1] = new T[i_count_gen];
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
	else {
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

template<class T>
void CIndividual<T>::operator++(int)
{
	vMutationHelper();
	d_fitness = 0;
	vSetFitness();
	d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);
	d_value_gen = c_knapsack->dGetValueFromGen(pi_genotype);
}

void CIndividual<int>::vMutationHelper()
{
	int i_mutation_value = 0;
	double d_number = 0;
	for (int i = 0; i < i_count_gen; i++)
	{
		d_number = dGenerateDouble(0.0, 1.0);
		if (!(d_number > d_mutation_prob))
		{
			i_mutation_value = iGenerateInteger((DEFAULT_MUTATION_VALUE)*(-1), DEFAULT_MUTATION_VALUE);
			pi_genotype[i] = pi_genotype[i] + i_mutation_value;
			if (pi_genotype[i] < 0) pi_genotype[i] = 0;
		}//if (!(d_number > d_mutation_prob))
	}//for (int i = 0; i < i_count_gen; i++)
}

void CIndividual<bool>::vMutationHelper()
{
	double d_number = 0;
	for (int i = 0; i < i_count_gen; i++)
	{
		d_number = dGenerateDouble(0.0, 1.0);
		if (!(d_number > d_mutation_prob))
		{
			pi_genotype[i] = !(pi_genotype[i]);
		}//if (!(d_number > d_mutation_prob))
	}//for (int i = 0; i < i_count_gen; i++)
}

void CIndividual<double>::vMutationHelper()
{
	double d_mutation_value = 0;
	double d_number = 0;
	for (int i = 0; i < i_count_gen; i++)
	{
		d_number = dGenerateDouble(0.0, 1.0);
		if (!(d_number > d_mutation_prob))
		{
			d_mutation_value = dGenerateDouble((DEFAULT_MUTATION_VALUE)*(-1), DEFAULT_MUTATION_VALUE);
			pi_genotype[i] = pi_genotype[i] + d_mutation_value;
			if (pi_genotype[i] < 0) pi_genotype[i] = 0;
		}//if (!(d_number > d_mutation_prob))
	}//for (int i = 0; i < i_count_gen; i++)
}

template<class T>
double CIndividual<T>::dGetFitness()
{
	return d_fitness;
}

template<class T>
T CIndividual<T>::iGetGen(int iIndex)
{
	return pi_genotype[iIndex];
}

template<class T>
double CIndividual<T>::dGetValueGen()
{
	return d_value_gen;
}

template<class T>
void CIndividual<T>::vDisplay()
{
	cout << "Fitness:	" << d_fitness << "	Size:		" << d_size_gen << "	[";
	for (int j = 0; j < i_count_gen - 1; j++)
	{
		cout << pi_genotype[j] << ",";
	}
	cout << pi_genotype[i_count_gen - 1] << "]" << endl;
}

template<class T>
void CIndividual<T>::vSetFitness()
{
	double d_size_gen = c_knapsack->dGetSizeFromGen(pi_genotype);

	if (d_size_gen <= c_knapsack->dGetKnapsackSize()) d_fitness = c_knapsack->dGetValueFromGen(pi_genotype);
}

template<class T>
int CIndividual<T>::iGenerateInteger(int iFrom, int iTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_int_distribution<> dis(iFrom, iTo);

	return dis(gen);
}

template<class T>
double CIndividual<T>::dGenerateDouble(double dFrom, double dTo)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(dFrom, dTo);

	return dis(gen);
}

