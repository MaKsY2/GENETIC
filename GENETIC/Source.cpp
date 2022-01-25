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