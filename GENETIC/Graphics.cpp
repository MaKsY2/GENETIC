#include "Graphics.h"
#include "Object.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>


using namespace sf;
using namespace std;

const float HEXAGON_SIZE = 20.f;

//const float HEXAGON_ERROR = 0;
const float HEXAGON_ERROR = 3 - sqrt(3);


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
	vector<Color>color(OBJECTS_CNT);
	color[ObjectType::BOT] = Color(240, 45, 58);
	color[ObjectType::NUN] = Color(255,255,255);
	color[ObjectType::FOOD] = Color(96, 153, 62);
	color[ObjectType::WALL] = Color(181, 127, 80);
	color[ObjectType::POISON] = Color(161, 103, 165);
	a.clear(Color(0, 0, 0, 0));
	CircleShape hexagon(HEXAGON_SIZE, 6);
	hexagon.setFillColor(Color(255, 200, 0));
	hexagon.setOutlineThickness(3.f);
	hexagon.setOutlineColor(Color(213, 207, 225));

	for (int i = 0; i < FIELD_ROWS; i++)
	{
		if (!(i % 2)) {
			hexagon.move(bool(i) * ((-2) * (HEXAGON_SIZE - HEXAGON_ERROR) * (FIELD_COLS-1)) + HEXAGON_SIZE, bool(i) * (HEXAGON_SIZE - 2*HEXAGON_ERROR) * (2));
		}
		else {
			hexagon.move((-2) * (HEXAGON_SIZE - HEXAGON_ERROR) * (FIELD_COLS-0.5), (HEXAGON_SIZE - 2*HEXAGON_ERROR) * (2));
		}
		for (int j = 0; j < FIELD_COLS; j++)
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
	RenderWindow window(VideoMode(1600, 900), "GENETIC", Style::Default, settings);
	MyGraphics graph(window);





	Map map1(FIELD_ROWS,FIELD_COLS);
	//map1.newEmptyMap();

	map1.foodMapFilling(20);
	map1.poisonMapFilling(20);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close(); 
		}
		graph.updateMap(map1.getField(), window);
		window.display();
	}
	return 0;
}