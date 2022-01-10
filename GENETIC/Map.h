#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <utility>
#include <vector>

#define MAX_FOOD_ELEMENTS 10
#define MAX_POISON_ELEMENTS 10
#define MAX_BOT_ELEMENTS 10
#define FIELD_ROWS 20
#define FIELD_COLS 32


class Map
{
public:
	Map(int height, int weight);
	~Map();
	std::vector<std::vector<int>> getField();
	void setObject(MyObject* objPtr, std::pair <int, int> aCoord);
	void newObjectOnField(ObjectType aType, std::pair <int, int> aCoord);
	void newEmptyMap();
	void poisonMapFilling(int cnt);
	void foodMapFilling(int cnt);
	std::pair<int, int> newRandCoords();

private:
	std::vector<std::vector<MyObject*>> mField;
};



#endif // !MAP_H
