#include "BOT.h"

Bot::Bot() :
	
	MyObject	(ObjectType::BOT),
	mHealth		(START_BOT_HEALTH),
	mPtr		(0),
	mDirection	(rand()%6)
{
	for (int i = 0; i < BOT_MEMORY; i++)
	{
		mProgram.push_back(rand() % 5);
	}
}


Bot::Bot(Bot& other):
	mHealth		(other.mHealth),
	mProgram	(other.mProgram),
	mPtr		(other.mPtr),
	mDirection	(other.mDirection)
{

}
//do nothing									0(nothing)		NUN
//change current direction						1(turn)			NUN
//eating food on current cell					2(eat)			EAT
//going on next cell							3(goForward)	FORWARD
//looking to next cell on current direction		4(look)			LOOK

Bot::Action Bot::run()
{
	if (mProgram[mPtr] == 0 || 
		mProgram[mPtr] == 1 )
	{
		return Action::NUN;
	}
	if (mProgram[mPtr] == 2)
	{
		return Action::EAT;
	}
	if (mProgram[mPtr] == 3)
	{
		return Action::FORWARD;
	}
	if (mProgram [mPtr] == 4)
	{
		return Action::LOOK;
	}
}

int
Bot::getHealth()
{
	return mHealth;
}

int
Bot::getDirection()
{
	return mDirection;
}

int 
Bot::getPtr()
{
	return mPtr;
}

std::vector<int> 
Bot::getProgram()
{
	return mProgram;
}

void 
Bot::feed(int cnt)
{
	mHealth += cnt;
}

void
Bot::hitting(int cnt)
{
	mHealth -= cnt;
}

void
Bot::mutation()
{
	int randCntMutation = rand() % mProgram.size();
	for (int i=0;i<randCntMutation;i++)
	{
		int ptr = rand() % mProgram.size();
		mProgram[ptr] = rand() % COMMAND_COUNT;
	}
}

Bot::~Bot()
{

}