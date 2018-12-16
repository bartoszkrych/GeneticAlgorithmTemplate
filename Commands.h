#pragma once
#include "MyCommand.h"
#include "CGeneticAlgorithm.h"

template<class T>
class CommandGA: public CMyCommand
{
public:
	void vRunCommand() override;

	CommandGA(int iPopulationSize, double dMutationProb, double dCrossProb,double dKnapsackSize,
		int iItemsCount, double dMaxValueItm, double dMaxSizeItm, double dSeconds);
	~CommandGA();

private:
	double d_knapsack_size;
	int i_items_count;
	int i_population_size;
	double d_mutation_prob;
	double d_cross_prob;
	double d_max_value;
	double d_max_size;
	double d_seconds;

};


template<class T>
void CommandGA<T>::vRunCommand()
{
	CKnapsackProblem<T> * c_knap = new CKnapsackProblem<T>();

	if (c_knap->bInitialObject(d_knapsack_size, i_items_count, d_max_value, d_max_size))
	{
		CGeneticAlgorithm<T> * c_ga = new CGeneticAlgorithm<T>();

		if (c_ga->bInitialObject(i_population_size, d_mutation_prob, d_cross_prob, c_knap))
		{
			c_knap->vDisplay();
			c_ga->vStartAlgorithm(d_seconds);

		}
		else
		{
			cout << "Something wrong with your genetic algorithm. Check your data!" << endl;
		}// ELSE if(c_ga->bInitialObject(i_population_size, d_mutation_prob, d_cross_prob, c_knap))
		delete c_ga;
	}
	else
	{
		cout << "Something wrong with your knapsack problem. Check your data!" << endl;
	} //ELSE if(c_knap->bInitialObject(d_capacity_knap, i_item_count, d_item_max_value, d_item_max_size))

	delete c_knap;

	cout << endl;
	system("pause");
}

template <class T>
CommandGA<T>::CommandGA(int iPopulationSize, double dMutationProb, double dCrossProb, double dKnapsackSize,
	int iItemsCount, double dMaxValueItm, double dMaxSizeItm, double dSeconds)
{
	d_knapsack_size = dKnapsackSize;
	i_items_count = iItemsCount;
	i_population_size = iPopulationSize;
	d_mutation_prob = dMutationProb;
	d_cross_prob = dCrossProb;
	d_max_value = dMaxValueItm;
	d_max_size = dMaxSizeItm;
	d_seconds = dSeconds;
}

template <class T>
CommandGA<T>::~CommandGA()
{
}

