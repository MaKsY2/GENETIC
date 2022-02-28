#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define MAX_FOOD_ELEMENTS 2
#define MAX_POISON_ELEMENTS 2
#define MAX_BOT_ELEMENTS 5
#define FIELD_ROWS 8
#define FIELD_COLS 8


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
	void botMapFilling(int cnt);
	MyObject* getObj(int y, int x);
	std::pair<int, int> newRandCoords();
	

	void makeTurn();

private:
	std::vector<std::vector<MyObject*>> mField;
	std::queue<std::pair<int, int>> bots;
};



#endif // !MAP_H
