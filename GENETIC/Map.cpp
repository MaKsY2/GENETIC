#include "Map.h"
#include "Object.h"

#include <iostream>
#include <map>
#include <vector>

using namespace std;

Map::Map()
{

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

vector<vector<int>>
Map::setField()
{
	
}