#pragma once
#include <cstddef>
#include <random>
#include <iostream>

using namespace std;

#define DEFAULT_SIZE 4
#define DEFAULT_VALUES 5
#define DEFAULT_KNAPSACK 7

template<class T>
class CKnapsackProblem
{
public:
	CKnapsackProblem()
	{
		d_knapsack_size = 0;
		i_items_count = 0;

		ppd_items_table = NULL;
	}

	~CKnapsackProblem()
	{
		for (int i = 0; i < i_items_count; i++)
		{
			delete[] ppd_items_table[i];
		}

		delete[] ppd_items_table;
	}

	bool bInitialObject(double dKnapsackSize, int iItemsCount, double dMaxValueItm, double dMaxSizeItm);
	bool bInitialObject(double dKnapsackSize, int iItemsCount);
	bool bSetNewValueOfItm(int iIndex, double iValue);
	bool bSetNewSizeOfItm(int iIndex, double iSize);
	double dGetValueFromGen(T * piTable);
	double dGetSizeFromGen(T * piTable);

	double dTest(T tTest) { return(0); };

	
	int iGetItemsCount();
	double dGetKnapsackSize();
	void vDisplay();
private:
	int iGenerateInteger(int iFrom, int iTo);
	double dGenerateDouble(double iFrom, double iTo);
	double d_knapsack_size;
	int i_items_count;
	double ** ppd_items_table;
	int i_population_size;
	double d_mutation_prob;
	double d_cross_prob;

};


template<>  double CKnapsackProblem<int>::dTest(int tTest) { return(1); };

#include "CKnapsackProblem.hpp"