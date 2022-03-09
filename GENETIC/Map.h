#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define MAX_FOOD_ELEMENTS 100
#define MAX_POISON_ELEMENTS 100
#define MAX_FOOD_CNT 250
#define MAX_POISON_CNT 250
#define MAX_BOT_ELEMENTS 32
#define K_TO_EVOLVE 16 //Coefficient to evolve
#define FIELD_ROWS 64
#define FIELD_COLS 36


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
	bool needEvolve();
	void evolve();

	int foodOnMap();
	int poisonOnMap();
	MyObject* getObj(int y, int x);
	std::pair<int, int> newRandCoords();
	

	void makeTurn();

private:
	std::vector<std::vector<MyObject*>> mField;
	std::queue<std::pair<int, int>> bots;
};



#endif // !MAP_H
