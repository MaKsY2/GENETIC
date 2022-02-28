#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Object.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>

#include "Map.h"


using namespace sf;
using namespace std;


class MyGraphics
{
public:
	MyGraphics(RenderWindow& mWindow, Font& aFont);
	virtual ~MyGraphics();
	void updateMap(vector<vector<int>> aMap, RenderWindow &a, Map& map1);
	void renderMap(RenderWindow& a);
private:
	RenderWindow& mWindow;
	Font& font;
};

#endif // !GRAPHICS_H