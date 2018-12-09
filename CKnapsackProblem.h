#pragma once
class CKnapsackProblem
{
public:
	CKnapsackProblem();
	CKnapsackProblem(double dKnapsackSize, int iItemsCount, double dMaxValueItm, double dMaxSizeItm);
	CKnapsackProblem(double dKnapsackSize, int iItemsCount);
	~CKnapsackProblem();

	bool bInitialObject(double dKnapsackSize, int iItemsCount, double dMaxValueItm, double dMaxSizeItm);
	bool bInitialObject(double dKnapsackSize, int iItemsCount);
	bool bSetNewValueOfItm(int iIndex, double iValue);
	bool bSetNewSizeOfItm(int iIndex, double iSize);
	double dGetValueFromGen(int * piTable);
	double dGetSizeFromGen(int * piTable);

	int iGetItemsCount();
	double dGetKnapsackSize();

	void vDisplay();
private:
	int iGenerateInteger(int iFrom, int iTo);
	double dGenerateDouble(double iFrom, double iTo);
	double d_knapsack_size;
	int i_items_count;
	double ** ppd_items_table;
};

