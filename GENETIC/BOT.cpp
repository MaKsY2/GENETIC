#include "BOT.h"




Bot::Bot() :
	
	MyObject	(ObjectType::BOT),
	mHealth		(START_BOT_HEALTH),
	mPtr		(0),
	mDirection	(rand()%6),
	mProgram    (BOT_MEMORY,NULL),
	nearCell    (ObjectType::NUN)
{
	for (int i = 0; i < BOT_MEMORY; i++)
	{
		mProgram[i] = (rand() % 5);
	}
}


Bot::Bot(Bot& other):
	mHealth		(other.mHealth),
	mProgram	(other.mProgram),
	mPtr		(other.mPtr),
	mDirection	(other.mDirection),
	nearCell	(other.nearCell)
{

}
//do nothing									0(nothing)		NUN
//change current direction						1(turn)			TURN
//eating food on current cell					2(eat)			EAT
//going on next cell							3(goForward)	FORWARD
//looking to next cell on current direction		4(look)			LOOK

Bot::Action Bot::run()
{
	if (mProgram[mPtr] == 0)
	{
		return Action::NUN;
	}
	if (mProgram[mPtr] == 1)
	{
		return Action::TURN;
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
	if (mProgram[mPtr] > 4  && mProgram[mPtr] <= 29)
	{
		mPtr += (mProgram[mPtr] - 4);
		if (mPtr >= BOT_MEMORY)
		{
			mPtr %= BOT_MEMORY;
		}
	}
	if (mProgram[mPtr] > 29 && mProgram[mPtr] <= 54)
	{
		mPtr -= (mProgram[mPtr] - 29);
		if (mPtr < 0)
		{
			mPtr = abs(mPtr) % BOT_MEMORY;
		}
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
Bot::setHealth(int cnt)
{
	mHealth = cnt;
}

void Bot::restoreHealth()
{
	mHealth = START_BOT_HEALTH;
}

void Bot::setCell(ObjectType near)
{
	nearCell = near;
}

void
Bot::setProgram(std::vector<int> aProgram)
{
	for (size_t i = 0; i < aProgram.size(); i++)
	{
		mProgram[i] = aProgram[i];
	}
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
Bot::randMutation()
{
	int randCntMutation = rand() % mProgram.size();
	for (int i=0;i<randCntMutation;i++)
	{
		int ptr = rand() % mProgram.size();
		mProgram[ptr] = rand() % COMMAND_COUNT;
	}
}

void
Bot::changeDir()
{
	int currentDir = mDirection;
	while (mDirection == currentDir) {
		mDirection = rand() % 6;
	}
}

void
Bot::shiftPtr()
{
	mPtr++;
	if (mPtr >= mProgram.size())
	{
		mPtr %= mProgram.size();
	}
}

void
Bot::fullMutation()
{
	for (int i = 0; i < mProgram.size(); i++)
	{
		mProgram[i] = rand() % 5;
	}
}

void
Bot::mutation(int ptr,int cnt)
{
	int range = ptr + cnt - 1;
	if (range > mProgram.size())
	{
		range = mProgram.size();
	}
	for (int i = ptr - 1; i < range; i++)
	{

		mProgram[i] = rand() % 5;
	}
}

void 
Bot::shiftPtrs(int cnt)
{
	mPtr += cnt;
	if (mPtr >= mProgram.size())
	{
		mPtr %= mProgram.size();
	}
}

Bot::~Bot()
{

}