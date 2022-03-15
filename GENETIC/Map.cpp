#include "Map.h"
#include "Object.h"

#include "BOT.h"
#include "FOOD.h"
#include "NUN.h"
#include "POISON.h"
#include "WALL.h"

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;


int dx0[] = { 0,-1,0, 1,1, 1 };
int dy0[] = { -1, 0,1,-1,0,-1 };

int dx1[] = { -1,-1,-1, 0,1, 0 };
int dy1[] = { -1, 0, 1,-1,0,-1 };

Map::Map(int height, int weight):
	mField					(height,vector<MyObject*>(weight,NULL))
{
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		for (int j = 0; j < FIELD_COLS; j++)
		{
			if (i == 0 || j == 0 || i == FIELD_ROWS - 1 || j == FIELD_COLS - 1)
			{
				setObject(new Wall(), make_pair(i, j));
			}
			else
			{
				setObject(new Nun(), make_pair(i, j));
			}
		}
	}
}

Map::~Map()
{

}

bool
Map::needEvolve()
{
	return (bots.size() <= MAX_BOT_ELEMENTS / K_TO_EVOLVE) ? true : false;
}

void
Map::evolve()
{
	int evolveCount = bots.size();
	for (size_t i = 0; i < evolveCount; i++)
	{ 
		pair<int, int> current = bots.front();
		Bot *botParent = static_cast<Bot*>(mField[current.first][current.second]);
		botParent->restoreHealth();
		for (size_t i = 1; i < K_TO_EVOLVE; i++)
		{
			pair<int, int> newBot = newRandCoords();
			setObject(new Bot(), newBot);
			bots.push(newBot);
			Bot* botSon = static_cast<Bot*>(mField[newBot.first][newBot.second]);
			botSon->setProgram(botParent->getProgram());
			botSon->randMutation();
			botSon->setHealth(START_BOT_HEALTH);
		}
		botParent->setHealth(START_BOT_HEALTH);
		
	}
	while (bots.size() != MAX_BOT_ELEMENTS)
	{
		pair<int, int> newBot = newRandCoords();
		setObject(new Bot(), newBot);
		bots.push(newBot);
	}
}
pair<int,int>
Map::randCoords()
{
	pair<int, int> s;
	s.first = rand() % FIELD_ROWS;
	s.second = rand() % FIELD_COLS;
	return s;
}

void Map::respawnFood(int cntTurn)
{
	if (!(cntTurn % TIME_TO_RESPAWN_FOOD))
	{
		int cnt = rand() % CNT_OF_RESPAWN_FOOD;

		for (int f = 0; f < cnt; f++)
		{
			pair<int, int> s;
			s = randCoords();
			while (mField[s.first][s.second]->getType() != ObjectType::FOOD)
			{
				s = randCoords();
			}
			int i = s.first;
			int j = s.second;
			for (int k = 0;k < 6;k++)
			{
				pair<int, int> p;
				if (i % 2 == 0)
				{
					p.first = i + dy0[k];
					p.second = j + dx0[k];
				}
				else
				{
					p.first = i + dy1[k];
					p.second = j + dx1[k];
				}
				if (mField[p.first][p.second]->getType() == ObjectType::NUN)
				{
					setObject(new Food(), p);
					break;
				}
			}
		}
	}
}

int Map::foodOnMap()
{
	int cnt = 0;
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		for (int j = 0;j < FIELD_COLS;j++)
		{
			if (mField[i][j]->getType() == ObjectType::FOOD)
			{
				cnt++;
			}
		}
	}
	return cnt;
}

int Map::poisonOnMap()
{
	int cnt = 0;
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		for (int j = 0;j < FIELD_COLS;j++)
		{
			if (mField[i][j]->getType() == ObjectType::POISON)
			{
				cnt++;
			}
		}
	}
	return cnt;
}

vector<vector<int>> 
Map::getField()
{
	vector<vector<int>> result;
	for (auto i : mField)
	{
		result.push_back({});
		for (auto j : i)
		{
			result.back().push_back(j->getType());
		}
	}
	return result;
}

void
Map::newObjectOnField(ObjectType aType, pair <int,int> aCoord)
{
	if (aType == ObjectType::BOT) setObject(new Bot(), aCoord);
	if (aType == ObjectType::FOOD) setObject(new Food(), aCoord);
	if (aType == ObjectType::NUN) setObject(new Nun(), aCoord);
	if (aType == ObjectType::POISON) setObject(new Poison(), aCoord);
	if (aType == ObjectType::WALL) setObject(new Wall(), aCoord);
}

void
Map::setObject(MyObject* objPtr, pair <int,int> aCoord)
{
	delete(mField[aCoord.first][aCoord.second]);
	mField[aCoord.first][aCoord.second] = objPtr;
}

void 
Map::newEmptyMap()
{
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		for (int j = 0; j < FIELD_COLS; j++)
		{
			if (i == 0 || j == 0 || i == FIELD_ROWS - 1 || j == FIELD_COLS - 1)
			{
				setObject(new Wall(), make_pair(i, j));
			}
			else
			{
				setObject(new Nun(), make_pair(i, j));
			}
		}
	}
}

void
Map::foodMapFilling(int cnt)
{
	while (cnt != 0)
	{
		setObject(new Food(), newRandCoords());
		cnt--;
	}
}


MyObject*
Map::getObj(int y, int x)
{
	return mField[y][x];
}


void
Map::makeTurn()
{
	int cnt = bots.size();
	for (int i = 0; i < cnt; i++)
	{
		pair<int, int> currentBot = bots.front();
		bots.pop();
		Bot* bot = static_cast<Bot*>(mField[currentBot.first][currentBot.second]);
		pair<int, int> nearCoord;
		if (currentBot.first % 2 == 0) {
			nearCoord.second = currentBot.second + dx0[bot->getDirection()];
			nearCoord.first = currentBot.first + dy0[bot->getDirection()];
		}
		else
		{
			nearCoord.second = currentBot.second + dx1[bot->getDirection()];
			nearCoord.first = currentBot.first + dy1[bot->getDirection()];
		}

		MyObject* nearObj = mField[nearCoord.first][nearCoord.second];
		switch (bot->run())
		{
		case Bot::Action::NUN:
			bot->shiftPtr();
			break;
		case Bot::Action::TURN:
			bot->changeDir();
			bot->shiftPtr();
			break;
		case Bot::Action::LOOK:
			bot->shiftPtr();
			break;
		case Bot::Action::EAT:
			switch (nearObj->getType())
			{
			case ObjectType::BOT:
				bot->shiftPtr();
				break;
			case ObjectType::FOOD:
				//  
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n'; // cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->feed(FOOD_ADD_HEALTH);
				bot->shiftPtr();
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::NUN:
				//
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->shiftPtr();
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::POISON:
				//
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->shiftPtr();
				bot->hitting(POISON_TAKE_HEALTH);
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::WALL:
				bot->shiftPtr();
				break;
			}
			break;
		case Bot::Action::FORWARD:
			switch (nearObj->getType())
			{
			case ObjectType::BOT:
				bot->shiftPtr();
				break;
			case ObjectType::FOOD:
				//
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->shiftPtr();
				bot->feed(FOOD_ADD_HEALTH / 2);
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::NUN:
				//
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->shiftPtr();
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::POISON:
				//
				// cout << setw(5) << currentBot.second + 1 << ' ' << currentBot.first + 1 << setw(5) << bot->getDirection() << setw(5) << nearCoord.second + 1 << ' ' << nearCoord.first + 1 << '\n';
				setObject(bot, nearCoord);
				mField[currentBot.first][currentBot.second] = new Nun();
				bot->shiftPtr();
				bot->hitting(POISON_TAKE_HEALTH / 2);
				currentBot = nearCoord;
				//bots.push(currentBot);
				break;
			case ObjectType::WALL:
				bot->shiftPtr();
				break;
			}
			break;
		}
		bot->hitting(1);
		int isLive = true;
		if (bot->getHealth() <= 0)
		{
			isLive = false;
			setObject(new Nun, currentBot);
		}

		//there is should be some fixes later 
		if (isLive) 
		{
			bots.push(currentBot);
		}
		//

	}
	//
}


void
Map::botMapFilling(int cnt)
{
	while (cnt != 0)
	{
		pair<int, int> botCoord = newRandCoords();
		bots.push(botCoord);
		setObject(new Bot(), botCoord);
		cnt--;
	}
}

void
Map::poisonMapFilling(int cnt)
{
	while (cnt != 0)
	{
		setObject(new Poison(), newRandCoords());
		cnt--;
	}
}

pair<int,int>
Map::newRandCoords()
{
	pair<int, int> newCoords(rand() % FIELD_ROWS, rand() % FIELD_COLS);
	while (mField[newCoords.first][newCoords.second]->getType() != ObjectType::NUN)
	{
		newCoords.first = rand() % FIELD_ROWS;
		newCoords.second = rand() % FIELD_COLS;
	}
	return newCoords;
}