#pragma once
#include "CKnapsackProblem.h"

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

#include "CIndividual.cpp"