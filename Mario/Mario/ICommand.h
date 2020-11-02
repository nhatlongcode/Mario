#pragma once

class CMario;

class ICommand
{
public:
	virtual void Execute(CMario* mario) = 0;
	virtual ~ICommand() {}
};