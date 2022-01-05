#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <vector>

#define MAX_FOOD_ELEMENTS 10
#define MAX_POISON_ELEMENTS 10
#define MAX_BOT_ELEMENTS 10
#define FIELD_ROWS 10
#define FIELD_COLS 10


class Map
{
public:
	Map();
	~Map();
	std::vector<vector<int>> getField();
	void setObject(MyObject* objPtr, pair<int, int> aCoord);
	void newObjectOnField(ObjectType aType, pair<int, int> aCoord);
	void newEmptyMap();
	void poisonMapFilling(int cnt);
	void foodMapFilling(int cnt);



private:
	std::vector<std::vector<MyObject*>> mField;
};



#endif // !MAP_H
