#include "Graphics.h"
#include "Object.h"
#include "Map.h"

#include "BOT.h"

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>


using namespace sf;
using namespace std;

const float HEXAGON_SIZE = 15.f;
const float OUTLINE_SIZE = HEXAGON_SIZE*3/20;


const float HEXAGON_ERROR = 3 - sqrt(3);


MyGraphics::MyGraphics(RenderWindow& aWindow, Font& aFont) :
	mWindow(aWindow),
	font(aFont)
{

}

MyGraphics::~MyGraphics()
{

}

void MyGraphics::renderMap(RenderWindow& a)
{

}

void MyGraphics:: updateMap(vector<vector<int>> aMap, RenderWindow &a,Map& map1 )
{
	vector<Color>color(OBJECTS_CNT);
	color[ObjectType::BOT] = Color(240, 45, 58);
	color[ObjectType::NUN] = Color(255,255,255);
	color[ObjectType::FOOD] = Color(96, 153, 62);
	color[ObjectType::WALL] = Color(181, 127, 80);
	color[ObjectType::POISON] = Color(161, 103, 165);
	a.clear(Color(0, 0, 0, 0));
	Text text;
	text.setFillColor(Color::Black);
	text.setCharacterSize(15.f);
	text.setFont(font);
	CircleShape hexagon(HEXAGON_SIZE, 6);
	hexagon.setFillColor(Color(255, 200, 0));
	hexagon.setOutlineThickness(OUTLINE_SIZE);
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
			if (aMap[i][j] == ObjectType::BOT)
			{
				Bot* bot = static_cast<Bot*>(map1.getObj(i, j));
				text.setPosition(hexagon.getPosition() + Vector2f{7.f,7.f});
				text.setString(to_string(bot->getHealth()));
				a.draw(text);
				
			}
		}
	}
}
