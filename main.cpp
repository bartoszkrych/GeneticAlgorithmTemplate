#include <iostream>
#include <random>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
using namespace std;

int main()
{
	int i_population_size = 5;
	double d_cross_prob = 0.6;
	double d_mutation_prob = 0.2;

	double d_seconds=2;
	double d_capacity_knap = 5.32;
	int i_item_count = 5;
	double d_item_max_value = 5.81;
	double d_item_max_size = 3.13;


	CKnapsackProblem * c_knap = new CKnapsackProblem();

	if(c_knap->bInitialObject(d_capacity_knap, i_item_count, d_item_max_value, d_item_max_size))
	{
		CGeneticAlgorithm * c_ga = new CGeneticAlgorithm();

		if(c_ga->bInitialObject(i_population_size, d_mutation_prob, d_cross_prob, c_knap))
		{
			c_knap->vDisplay();
			//c_ga->vGenerateNewPopulation();
			c_ga->vStartAlgorithm(d_seconds);

			delete c_ga;
		}
		else
		{
			cout << "Something wrong with your genetic algorithm. Check your data!"<<endl;
			delete c_ga;
		}// ELSE if(c_ga->bInitialObject(i_population_size, d_mutation_prob, d_cross_prob, c_knap))
	}
	else
	{
		cout << "Something wrong with your knapsack problem. Check your data!" << endl;
	} //ELSE if(c_knap->bInitialObject(d_capacity_knap, i_item_count, d_item_max_value, d_item_max_size))

	delete c_knap;

	_CrtDumpMemoryLeaks();
	system("pause");
	
	return 0;
}
