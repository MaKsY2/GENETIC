#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define MAX_FOOD_ELEMENTS 10
#define MAX_POISON_ELEMENTS 10
#define MAX_BOT_ELEMENTS 10
#define FIELD_ROWS 20
#define FIELD_COLS 32

int dx[] = { -1,-1,-1, 0, 1, 0 };
int dy[] = {  1, 0,-1, 1, 0,-1 };

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
	std::pair<int, int> newRandCoords();
	

	void makeTurn();

private:
	std::vector<std::vector<MyObject*>> mField;
	std::queue<std::pair<int, int>> bots;
};



#endif // !MAP_H
