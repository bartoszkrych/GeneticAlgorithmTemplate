#pragma once
class CMyCommand
{
public:
	virtual void vRunCommand() = 0;
	virtual ~CMyCommand() = default;
};

