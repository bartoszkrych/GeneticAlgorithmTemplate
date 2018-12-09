#include "CGeneticAlgorithm.h"
#include <random>
#include <iostream>
#include <chrono>

template<class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm()
{
	i_population_size = 0;
	d_mutation_prob = 0;
	d_cross_prob = 0;
	pc_knapsack_problem = NULL;
	ppc_tab_population = NULL;
	pc_best_individual = NULL;
}

template<class T>
CGeneticAlgorithm<T>::~CGeneticAlgorithm()
{
	for (int i = 0; i<i_population_size; i++)
	{
		if(ppc_tab_population[i]!=pc_best_individual)
		delete ppc_tab_population[i];
	}

	delete[] ppc_tab_population;
	delete pc_best_individual;
}

template<class T>
bool CGeneticAlgorithm<T>::bInitialObject(int iPopulationSize, double dMutationProb, double dCrossProb,
	CKnapsackProblem<T>* cKnapsackProblem)
{
	if(dMutationProb >= 0
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
	while (((double)clock() - start)/ CLOCKS_PER_SEC <dTime )
	{
		vGenerateNewPopulation();
		i_iter_population++;
	}
	std::cout << "###	LAST POP	###" << std::endl;
	for (int i = 0; i < i_population_size; i++)
	{
		ppc_tab_population[i]->vDisplay();
	}

	std::cout <<i_iter_population <<"THE BEST IS: " << std::endl; pc_best_individual->vDisplay();
}//CGeneticAlgorithm<T>::vGeneratePopulation(int iIter)

template<class T>
void CGeneticAlgorithm<T>::vGenerateNewPopulation()
{
	std::cout << "###	POP	###"<< std::endl;
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
			CIndividual<T>* c_child = (*ppc_tab_population[pi_parents[0]])+ppc_tab_population[pi_parents[1]];
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
	if(cToMatch->dGetFitness()>pc_best_individual->dGetFitness())
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