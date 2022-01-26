#include "BOT.h"
#include "Map.h"
#include "Graphics.h"

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1600, 900), "GENETIC", Style::Default, settings);
	MyGraphics graph(window);



	Map map1(FIELD_ROWS, FIELD_COLS);
	//map1.newEmptyMap();

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
		graph.updateMap(map1.getField(), window);
		window.display();
		map1.makeTurn();
		vector<vector<int>>ff = map1.getField();
		graph.updateMap(map1.getField(), window);
		window.display();
	}
	return 0;
}