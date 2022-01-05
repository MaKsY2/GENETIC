#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Object.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <vector>


using namespace sf;
using namespace std;


class MyGraphics
{
public:
	MyGraphics(RenderWindow& mWindow);
	virtual ~MyGraphics();
	void updateMap(vector<vector<int>> aMap, RenderWindow &a);
	void renderMap(RenderWindow& a);
private:
	RenderWindow& mWindow;
};

#endif // !GRAPHICS_H