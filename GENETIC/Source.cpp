#include "BOT.h"
#include "Map.h"
#include "Graphics.h"



void timeStamp(Event &event)
{
	long long timeStamper = 1 * 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8 * 8;
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


	Map map1(FIELD_ROWS, FIELD_COLS);

	map1.foodMapFilling(MAX_FOOD_ELEMENTS);
	map1.poisonMapFilling(MAX_POISON_ELEMENTS);
	map1.botMapFilling(MAX_BOT_ELEMENTS);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		graph.updateMap(map1.getField(), window, map1);
		window.display();

		timeStamp(event);
		map1.makeTurn();
		cntTurn++;

		if (map1.needEvolve())
		{
			map1.evolve();
			if (map1.foodOnMap() <= MAX_FOOD_CNT - MAX_FOOD_ELEMENTS)
			{
				map1.foodMapFilling(MAX_FOOD_ELEMENTS);
			}
			if (map1.poisonOnMap() <= MAX_POISON_CNT - MAX_POISON_ELEMENTS)
			{
				map1.poisonMapFilling(MAX_POISON_ELEMENTS);
			}
			//map1.foodMapFilling(MAX_FOOD_ELEMENTS);
			//map1.poisonMapFilling(MAX_POISON_ELEMENTS);
			epoch++;
			std::cout << "Epoch: " << epoch << "Life period: " << cntTurn << std::endl;
			cntTurn = 0;

		}



		//vector<vector<int>>ff = map1.getField();
		//graph.updateMap(map1.getField(), window);
		//window.display();
	}
	return 0;
}