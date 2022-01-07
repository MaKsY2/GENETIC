#include "Map.h"
#include "Object.h"

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
				setObject(new MyObject(ObjectType::WALL), make_pair(j, i));
			}
			else
			{
				setObject(new MyObject(ObjectType::NUN), make_pair(j, i));
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
				setObject(new MyObject(ObjectType::WALL), make_pair(j, i));
			}
			else
			{
				setObject(new MyObject(ObjectType::NUN), make_pair(j, i));
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
	}
}

void
Map::poisonMapFilling(int cnt)
{
	while (cnt != 0)
	{
		setObject(new MyObject(ObjectType::POISON), newRandCoords());
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