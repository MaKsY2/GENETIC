#ifndef MAP_H
#define MAP_H

#include "Object.h"

#include <iostream>
#include <vector>



class Map
{
public:
	Map();
	~Map();
	std::vector<std::vector<int>> getField();

private:
	std::vector<std::vector<MyObject*>> mField;
};



#endif // !MAP_H
