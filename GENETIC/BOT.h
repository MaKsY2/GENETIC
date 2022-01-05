#ifndef BOT_H
#define BOT_H

#include "Object.h"

#include <vector>

class BOT : public MyObject
{
	enum Action 
	{
		NUN, 
		FORWARD, 
		LOOK, 
		EAT
	};

public:
	BOT();
	virtual ~BOT();
	Action run();

private:
	int health;
	std::vector<int> mProgram;
	int ptr;
};

#endif BOT_H