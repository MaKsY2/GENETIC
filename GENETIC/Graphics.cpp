#include "graphics.h"
#include "Object.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>


using namespace sf;
using namespace std;

const float HEXAGON_SIZE = 20.f;
const float FIELD_ROWS = 10.f;
const float FIELD_COLS = 10.f;

const float HEXAGON_ERROR = 2 - sqrt(3) - 0.01;


MyGraphics::MyGraphics(RenderWindow& aWindow) :
	mWindow(aWindow)
{

}

MyGraphics::~MyGraphics()
{

}

void MyGraphics::renderMap(RenderWindow& a)
{

}
void MyGraphics:: updateMap(vector<vector<int>> aMap, RenderWindow &a)
{
	vector<Color>color;
	for (int i = 0; i < OBJECTS_CNT; i++)
	{
		color[i] = Color(i * 50, i * 50, i * 50);
	}
	a.clear(Color(0, 0, 0, 0));
	CircleShape hexagon(HEXAGON_SIZE, 6);
	hexagon.setFillColor(Color(255, 200, 0));
	for (int i = 0; i < FIELD_ROWS; i++)
	{
		if (!(i % 2)) {
			hexagon.move(bool(i) * ((-2) * (HEXAGON_SIZE - HEXAGON_ERROR) * (FIELD_COLS)) + HEXAGON_SIZE, bool(i) * (HEXAGON_SIZE - HEXAGON_ERROR) * (2));
		}
		else {
			hexagon.move((-2) * (HEXAGON_SIZE - HEXAGON_ERROR) * (FIELD_COLS - 0.5), (HEXAGON_SIZE - HEXAGON_ERROR) * (2));
		}
		for (int j = 0; j < FIELD_COLS + i % 2; j++)
		{
			hexagon.setFillColor(color[aMap[i][j]]);
			hexagon.move((HEXAGON_SIZE - HEXAGON_ERROR) * (2) * bool(j), 0);
			a.draw(hexagon);
		}
	}
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(500, 500), "GENETIC", Style::Default, settings);
	MyGraphics::updateMap(Map::getField(),window)
	
	return 0;
}