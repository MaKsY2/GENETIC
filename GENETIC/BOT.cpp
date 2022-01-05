#include "BOT.h"

BOT::BOT() :
	
	MyObject	(ObjectType::BOT),
	health		(0),
	ptr			(0)
{
	for (int i = 0; i < mProgram.size(); i++)
	{
		mProgram[i] = rand() % 5;
	}
}
//do nothing									0(nothing)		NUN
//change current direction						1(turn)			NUN
//eating food on current cell					2(eat)			EAT
//going on next cell							3(goForward)	FORWARD
//looking to next cell on current direction		4(look)			LOOK

BOT::Action BOT::run()
{
	if (mProgram[ptr] == 0 || 
		mProgram[ptr] == 1 )
	{
		return Action::NUN;
	}
	if (mProgram[ptr] == 2)
	{
		return Action::EAT;
	}
	if (mProgram[ptr] == 3)
	{
		return Action::FORWARD;
	}
	if (mProgram [ptr] == 4)
	{
		return Action::LOOK;
	}
}

BOT::~BOT()
{

}