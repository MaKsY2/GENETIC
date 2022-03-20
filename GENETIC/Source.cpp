#define _CRT_SECURE_NO_WARNINGS

#include "BOT.h"
#include "Map.h"
#include "Graphics.h"



void timeStamp(Event &event)
{
	size_t timeStamper = 1 * 8 * 8 * 8 * 8 * 8;
	for (long long i = 0; i < timeStamper; i++)
	{
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code)
			{
			case sf::Keyboard::Key::Up:
				timeStamper *= 8;
				break;
			case sf::Keyboard::Key::Down:
				timeStamper /= 8;
				break;
			case sf::Keyboard::Key::Tab:
				timeStamper = 1;
				break;
			default:
				break;
			}
		}
	}
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1600, 900), "GENETIC", Style::Default, settings);
	Font font;
	font.loadFromFile("20989.ttf");
	MyGraphics graph(window, font);
	size_t epoch = 0;
	size_t cntTurn = 0;
	
	std::cout << "Epoch;" << "Life period" << std::endl;


	Map map1(FIELD_ROWS, FIELD_COLS);

	map1.foodMapFilling(MAX_FOOD_ELEMENTS);
	map1.poisonMapFilling(MAX_POISON_ELEMENTS);
	map1.botMapFilling(MAX_BOT_ELEMENTS);
	map1.wallMapFilling(MAX_WALL_ELEMENTS);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//graph.updateMap(map1.getField(), window, map1);
		window.display();

		timeStamp(event);
		map1.makeTurn();
		cntTurn++;
#ifdef FOOD
		map1.respawnFood(cntTurn);
#endif
		if (MAX_FOOD_ELEMENTS >= map1.foodOnMap() + MAX_BOT_ELEMENTS) {

			map1.foodRandFill();
		}
		if (MAX_POISON_ELEMENTS >= map1.poisonOnMap() + MAX_BOT_ELEMENTS) {

			map1.poisonRandFill();
		}

		if (map1.needEvolve())
		{
			map1.evolve();

#ifdef FOOD_AND_POSION
			if (map1.foodOnMap() <= MAX_FOOD_ELEMENTS)
			{
				map1.foodMapFilling(MAX_FOOD_ELEMENTS);
			}
			if (map1.poisonOnMap() <= MAX_POISON_ELEMENTS)
			{
				map1.poisonMapFilling(MAX_POISON_ELEMENTS);
			}
#endif
			//map1.foodMapFilling(MAX_FOOD_ELEMENTS);
			//map1.poisonMapFilling(MAX_POISON_ELEMENTS);
			epoch++;
			std::cout << epoch << ";" << cntTurn << std::endl;
			freopen("info.txt", "a", stdout);
			std::cout << epoch << ";" << cntTurn << std::endl;
			freopen("CON", "w", stdout);
			cntTurn = 0;

		}



		//vector<vector<int>>ff = map1.getField();
		//graph.updateMap(map1.getField(), window);
		//window.display();
	}
	return 0;
}