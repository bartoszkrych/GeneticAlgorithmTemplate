#pragma once
#include "CKnapsackProblem.h"
#include "CIndividual.h"

template<class T>
class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm();
	~CGeneticAlgorithm();

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

