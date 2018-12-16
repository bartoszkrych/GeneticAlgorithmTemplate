#include <iostream>
#include <random>
#include "MyMenu.h"
#include "MenuCommand.h"
#include "Commands.h"
using namespace std;


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>


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

	CMyMenu* c_main = new CMyMenu("Main", "main");

	 CMenuCommand * c_algorithm = new CMenuCommand("Start genetic algorithm.","start",
		new CommandGA<int>(i_population_size,d_mutation_prob,d_cross_prob,
		d_capacity_knap,i_item_count,d_item_max_value,d_item_max_size,d_seconds),
		"genetic algorithm");

	c_main->vAddItem(c_algorithm);
	c_main->vRun();

	delete c_main;
	cout << endl;
	system("pause");
	_CrtDumpMemoryLeaks();
	return 0;
}
