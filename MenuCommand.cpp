#include "MenuCommand.h"
#include <iostream>

const std::string DEFAULT_NAME = "Default name";
const std::string DEFAULT_COMMAND = "defcom";

void CMenuCommand::vRun()
{
	if (c_command != NULL)
	{
		c_command->vRunCommand();
	}
	else
	{
		std::cout << std::endl << "Command is empty." << std::endl << std::endl;
		system("pause");
	}

}

std::string CMenuCommand::sToString()
{
	return s_name + " (" + s_command + ")";
}

std::string CMenuCommand::sGetCommand()
{
	return s_command;
}

void CMenuCommand::vSetHelp(std::string sHelp)
{
	s_help = sHelp;
}

std::string CMenuCommand::sGetHelp()
{
	return s_help;
}

void CMenuCommand::vSetRoot(CMenuItem* cRoot)
{
	c_root = cRoot;
}

CMenuItem* CMenuCommand::cGetRoot()
{
	return c_root;
}

CMenuItem* CMenuCommand::cSearchObject(std::string sCommand, CMenuItem* cMenu)
{
	return NULL;
}

void CMenuCommand::vGetStringToParsing(std::string& sString)
{
	std::string s_command_pars = "['" + s_name + "','" + s_command + "','" + s_help + "']";
	sString += s_command_pars;
}

CMenuCommand::CMenuCommand()
{
	s_name = DEFAULT_NAME;
	s_command = DEFAULT_COMMAND;
	c_command = NULL;
}

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, CMyCommand * cCommand, std::string sHelp)
{
	s_name = sName;
	s_command = sCommand;
	c_command = cCommand;
	s_help = sHelp;
}

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sHelp)
{
	s_name = sName;
	s_command = sCommand;
	s_help = sHelp;
	c_command = NULL;
}

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand)
{
	s_name = sName;
	s_command = sCommand;
	c_command = NULL;
}

CMenuCommand::CMenuCommand(CMyCommand* cCommand)
{
	s_name = DEFAULT_NAME;
	s_command = DEFAULT_COMMAND;
	c_command = cCommand;
}

CMenuCommand::~CMenuCommand()
{
	std::cout << std::endl << "Deleting command";
	if (c_command != NULL)
	{
		delete c_command;
	}
}

void CMenuCommand::vDeleteChange(CMenuItem* cMenu)
{
}
