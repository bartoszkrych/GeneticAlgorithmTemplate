#pragma once
#include "CKnapsackProblem.h"
#include "CIndividual.h"

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

#include "CGeneticAlgorithm.cpp"