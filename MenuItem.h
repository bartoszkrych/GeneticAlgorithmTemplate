#pragma once
#include <string>

class CMenuItem
{
public:
	virtual void vRun() = 0;
	virtual std::string sToString() = 0;
	virtual std::string sGetCommand() = 0;
	virtual std::string sGetHelp() = 0;
	virtual void vSetRoot(CMenuItem* cRoot) = 0;
	virtual CMenuItem* cGetRoot() = 0;
	virtual CMenuItem* cSearchObject(std::string sCommand, CMenuItem* cMenu) = 0;
	virtual void vGetStringToParsing(std::string &sString) = 0;


	virtual void  vDeleteChange(CMenuItem * cMenu) = 0;

	virtual ~CMenuItem() = default;
protected:
	std::string s_command;
	std::string s_name;
	std::string s_help;
	CMenuItem* c_root = nullptr;
};

