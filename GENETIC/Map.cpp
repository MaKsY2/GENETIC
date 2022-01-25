#include "Map.h"
#include "Object.h"
#include "BOT.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

Map::Map(int height, int weight):
	mField					(height,vector<MyObject*>(weight,NULL))
{
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		for (int j = 0; j < FIELD_COLS; j++)
		{
			if (i == 0 || j == 0 || i == FIELD_ROWS - 1 || j == FIELD_COLS - 1)
			{
				setObject(new MyObject(ObjectType::WALL), make_pair(i, j));
			}
			else
			{
				setObject(new MyObject(ObjectType::NUN), make_pair(i, j));
			}
		}
	}
}

Map::~Map()
{

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
	if (aType == ObjectType::BOT) setObject(new MyObject(ObjectType::BOT), aCoord);
	if (aType == ObjectType::FOOD) setObject(new MyObject(ObjectType::FOOD), aCoord);
	if (aType == ObjectType::NUN) setObject(new MyObject(ObjectType::NUN), aCoord);
	if (aType == ObjectType::POISON) setObject(new MyObject(ObjectType::POISON), aCoord);
	if (aType == ObjectType::WALL) setObject(new MyObject(ObjectType::WALL), aCoord);
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
				setObject(new MyObject(ObjectType::WALL), make_pair(i, j));
			}
			else
			{
				setObject(new MyObject(ObjectType::NUN), make_pair(i, j));
			}
		}
	}
}

void
Map::foodMapFilling(int cnt)
{
	while (cnt != 0)
	{
		setObject(new MyObject(ObjectType::FOOD), newRandCoords());
		cnt--;
	}
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
		nearCoord.first = currentBot.first + dx[bot->getDirection()];
		nearCoord.second = currentBot.second + dy[bot->getDirection()];
		MyObject* nearObj = mField[nearCoord.first][nearCoord.second];
		switch (bot->run())
		{
		case Bot::Action::NUN:
			break;
		case Bot::Action::EAT:
			switch (nearObj->getType())
			{
			case ObjectType::BOT:
				break;
			case ObjectType::FOOD:
				//  
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				bot->feed(FOOD_ADD_HEALTH);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::NUN:
				//
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::POISON:
				//
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				bot->hitting(POISON_TAKE_HEALTH);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::WALL:
				break;
			}
			break;
		case Bot::Action::FORWARD:
			switch (nearObj->getType()) 
			{
			case ObjectType::BOT:
				break;
			case ObjectType::FOOD:
				//
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				bot->feed(FOOD_ADD_HEALTH/2);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::NUN:
				//
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::POISON:
				//
				setObject(bot, nearCoord);
				setObject(new MyObject(ObjectType::NUN), currentBot);
				bot->hitting(POISON_TAKE_HEALTH/2);
				currentBot = nearCoord;
				bots.push(currentBot);
				break;
			case ObjectType::WALL:
				break;
			}
			break;
		}

	}
}


void
Map::botMapFilling(int cnt)
{
	while (cnt != 0)
	{
		pair<int, int> botCoord = newRandCoords();
		bots.push(botCoord);
		setObject(new MyObject(ObjectType::BOT), botCoord);
		cnt--;
	}
}

void
Map::poisonMapFilling(int cnt)
{
	while (cnt != 0)
	{
		setObject(new MyObject(ObjectType::POISON), newRandCoords());
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