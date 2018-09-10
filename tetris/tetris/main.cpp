#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;


const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
}a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, //I
	2,4,5,7, //Z
	3,5,4,6, //S
	3,5,4,7, //T
	2,3,5,7, //L
	3,5,7,6, //J
	2,3,4,5, //O
};

bool check()
{
	for (int i = 0; i < 4; ++i)
	{
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;
	}
}

int main()
{
	RenderWindow window(VideoMode(300, 500), "Tetris");

	Texture texture;
	texture.loadFromFile("images/tiles.png");

	Sprite sprite(texture);
	sprite.setTextureRect(IntRect(0, 0, 18, 18));

	int dx = 0; bool rotate = 0; int colorNum = 1;
	float timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Up) rotate = true;
				else if (event.key.code == Keyboard::Left) dx = -1;
				else if (event.key.code == Keyboard::Right) dx = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		else delay = 0.3;
		// -MOVE- //
		for (int i = 0; i < 4; ++i) 
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!check())
			for (int i = 0; i < 4; ++i)
				a[i] = b[i];

		// -ROTATE- //
		if (rotate)
		{
			Point point = a[1];
			for (int i = 0; i < 4; ++i)
			{
				int y = a[i].x - point.x;
				int x = a[i].y - point.y;
				a[i].x = point.x - x;
				a[i].y = point.y + y;
			}
			if (!check())
				for (int i = 0; i < 4; ++i)
					a[i] = b[i];
		}

		// -Tick- //
		if (timer > delay)
		{
			for (int i = 0; i < 4; ++i)
			{
				b[i] = a[i];
				a[i].y += 1;
			}
			if (!check())
			{
				for (int i = 0; i < 4; ++i)
				{
					field[b[i].y][b[i].x] = colorNum;
				}
				colorNum = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; ++i)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}

			timer = 0;
		}


		/*int n = 3;
		if(a[0].x==0)
		for (int i = 0; i < 4; i++) {
			a[i].x = figures[n][i] % 2;
			a[i].y = figures[n][i] / 2;
		}*/

		dx = 0; rotate = 0;

		// -Draw- //
		window.clear(Color::Red);

		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				sprite.setPosition(j * 18, i * 18);
				window.draw(sprite);

			}
		for (int i = 0; i < 4; i++) {
			sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			sprite.setPosition(a[i].x * 18, a[i].y * 18);
			window.draw(sprite);
		}
		window.draw(sprite);
		window.display();
	}

	return 0;
}