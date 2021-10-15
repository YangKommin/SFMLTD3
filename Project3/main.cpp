#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
	Clock m_clock;
	Time m_elapsed;
	RenderWindow window(VideoMode(1250, 750), "Mon Petit Jeu SFML!");

	RectangleShape shape(Vector2f(1250.0f, 750.0f));
	shape.setFillColor(Color::White);

	Texture texture;
	Sprite sprite;

	texture.loadFromFile("../ressources/textures/link.png");
	sprite.setTexture(texture);
	sprite.setPosition(Vector2f(150.f, 200.f));
	sprite.setScale(Vector2f(3, 3));

	IntRect irect = { 0,0,17,23 };
	sprite.setTextureRect(irect);
	float animTime = 0.0f;
	int frameX = 0;
	int frameY = 0;
	float dirX = 1;
	float dirY = 1;

	Texture texture2;
	texture2.loadFromFile("../ressources/textures/Pack.jpg");
	Sprite sprite2;
	sprite2.setTexture(texture2);

	Shader shader;
	RenderStates rs;

	float timer = 0;

	Vector2f vect(1250.0f, 750.0f);

	while (window.isOpen())
	{
		m_elapsed = m_clock.restart(); // restart the clock

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		timer += m_elapsed.asSeconds();

		shader.loadFromFile("../ressources/shaders/helloworld.frag.txt", Shader::Type::Fragment);
		rs.shader = &shader;
		rs.blendMode = BlendAlpha;
		rs.transform = Transform::Identity;
		rs.texture = NULL;
		shader.setUniform("u_time", timer);
		//shader.setUniform("u_resolution", vect);
		shader.setUniform("currentTexture", texture);

		window.clear();

		window.draw(sprite, &shader);

		animTime += m_elapsed.asSeconds();
		if (Keyboard::isKeyPressed(Keyboard::Down) && animTime > 0.2)
		{
			frameX++;
			frameY = 0;
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;
			irect.top = frameY * irect.height;
			sprite.setTextureRect(irect);
			sprite.move(0 * animTime, 30 * animTime);
			animTime = 0.0f;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && animTime > 0.2)
		{
			frameX++;
			frameY = 1;
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;
			irect.top = frameY * irect.height;
			sprite.setTextureRect(irect);
			sprite.move(30 * animTime, 0 * animTime);
			animTime = 0.0f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && animTime > 0.2)
		{
			frameX++;
			frameY = 2;
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;
			irect.top = frameY * irect.height;
			sprite.setTextureRect(irect);
			sprite.move(-30 * animTime, 0 * animTime);
			animTime = 0.0f;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && animTime > 0.2)
		{
			frameX++;
			frameY = 3;
			if (frameX > 8) frameX = 0;
			irect.left = frameX * irect.width;
			irect.top = frameY * irect.height;
			sprite.setTextureRect(irect);
			sprite.move(0 * animTime, -30 * animTime);
			animTime = 0.0f;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) &&
			!Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left))
		{
			frameX = 0;
			irect.left = frameX * irect.width;
			irect.top = frameY * irect.height;
			sprite.setTextureRect(irect);
			animTime = 0.0f;
		}

		window.display();
	}
	return 1;
}