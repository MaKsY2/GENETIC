#ifndef BOT_H
#define BOT_H

#include "Object.h"

#include <vector>

//enum Action
//{
//	NUN,
//	FORWARD,
//	LOOK,
//	EAT
//};

//std::vector<Action> commands =
//{
//	NUN,
//	NUN,
//	EAT,
//	FORWARD,
//	LOOK
//}; 


class Bot : public MyObject
{
public:

	enum Action
	{
		NUN,
		FORWARD,
		LOOK,
		EAT,
		TURN
	};

	Bot();
	Bot(Bot& other);
	virtual ~Bot();
	Action run();


	void feed(int cnt);
	void hitting(int cnt);
	void changeDir();
	void shiftPtrs(int cnt);
	void shiftPtr();
	void fullMutation();
	void mutation(int ptr, int cnt);
	void randMutation();

	int getHealth();
	int getDirection();
	int getPtr();

	std::vector<int> getProgram();


private:

	int mHealth;
	std::vector<int> mProgram;
	int mPtr;
	int mDirection;
};

#endif BOT_H