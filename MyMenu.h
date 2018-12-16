#pragma once
#include <vector>
#include "MenuItem.h"
#include <string>
using namespace std;


class CMyMenu : public CMenuItem
{
public:
	void vAddItem(CMenuItem * newItem);
	bool bDeleteItem(int iIndex);
	void vShowItems();
	void vSearchCommand(std::string sCommand);
	string sSaveToString();

	void vRun() override;
	string sToString() override;
	string sGetCommand() override;
	std::string sGetHelp() override;
	void vSetRoot(CMenuItem* cRoot) override;
	CMenuItem* cGetRoot() override;
	void vGetStringToParsing(string &sString) override;
	CMenuItem* cSearchObject(string sCommand, CMenuItem* cMenu) override;


	void  vDeleteChange(CMenuItem * cMenu) override;
	CMenuItem * cGetRootOfTree();

	CMyMenu();
	CMyMenu(string sName, string sCommand);
	~CMyMenu();
private:
	std::vector<CMenuItem*>  v_menu_items;
	int i_size;
	string s_path;
	std::string s_help;
	CMenuItem*  c_root;

	bool bTestCommand(string test);
	int iFindCommand(string sCommand);
};

