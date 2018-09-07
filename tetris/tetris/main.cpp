#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(300, 500), "Tetris");

	Texture texture;
	texture.loadFromFile("images/tiles.png");

	Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		window.clear(Color::Cyan);
		window.draw(sprite);
		window.display();
	}

	return 0;
}