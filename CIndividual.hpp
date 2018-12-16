/*
using namespace std;



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
			pi_genotype[i] = !(pi_genotype[i]) ;
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
	cout << "Fitness:	" << d_fitness <<"	Size:		" << d_size_gen<< "	[";
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

*/