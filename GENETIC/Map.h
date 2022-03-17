#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

#define MAX_FOOD_ELEMENTS 144
#define MAX_POISON_ELEMENTS 144
#define MAX_WALL_ELEMENTS 77
#define MAX_BOT_ELEMENTS 32
#define CNT_OF_RESPAWN_FOOD MAX_FOOD_ELEMENTS/4
#define TIME_TO_RESPAWN_FOOD 10
#define K_TO_EVOLVE MAX_BOT_ELEMENTS/4 //Coefficient to evolve
#define FIELD_ROWS 18
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
	void botMapFilling(int cnt);
	void wallMapFilling(int cnt);

	void foodRandFill();
	void poisonRandFill();

	bool needEvolve();
	void evolve();

	void respawnFood(int cntTurn);
	//void respawnPoison(int cntTurn);

	int foodOnMap();
	int poisonOnMap();

	MyObject* getObj(int y, int x);

	std::pair<int, int> newRandCoords();
	std::pair<int, int> randCoords();
	

	void makeTurn();

private:
	std::vector<std::vector<MyObject*>> mField;
	std::queue<std::pair<int, int>> bots;
};



#endif // !MAP_H
