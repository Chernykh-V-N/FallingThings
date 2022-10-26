#pragma comment(lib,"Box2D.lib")
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")

#include <iostream>

#include <SFML/Graphics.hpp>
#include <time.h>
#include <cmath>

#include "ball.h"
#include "falling_object.h"

#include <box2d/box2d.h>


using namespace std;
using namespace sf;


//Глобальные переменные и объекты
Ball ball; //Мяч

float wanted_fps(100); //FPS


int main()
{
	//Таймер для регулировки скорости работы
	sf::Clock loop_timer;

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	//window.setFramerateLimit(60);

	//Счетчик FPS
	int fps(0);

	time_t tmp1, tmp2;
	tmp1 = time(NULL);


	//----ТЕКСТУРЫ----

	//Задник
	Texture background_texture;
	background_texture.loadFromFile("Graphics\\background_1.png");

	//Границы
	Texture border_horizontal_texture, border_vertical_texture;
	border_horizontal_texture.loadFromFile("Graphics\\border_horizontal.png");
	border_vertical_texture.loadFromFile("Graphics\\border_vertical.png");

	//Объекты
	Texture box_texture;
	box_texture.loadFromFile("Graphics\\Box.png");
	
	//Мяч
	Texture ball_texture;
	ball_texture.loadFromFile("Graphics\\ball_1.png");
	

	//----СПРАЙТЫ----

	//Задник
	Sprite background_sprite(background_texture);

	//Границы
	Sprite border_horizontal_l_sprite(border_horizontal_texture);
	Sprite border_horizontal_r_sprite(border_horizontal_texture);
	Sprite border_vertical_sprite(border_vertical_texture);

	border_horizontal_r_sprite.setPosition(790, 0);
	border_vertical_sprite.setPosition(0, 590);

	//Объекты
	Sprite box_sprite(box_texture);
	
	//Мяч
	Sprite ball_sprite(ball_texture);
	
	//Таймер для просчета физики(вторая переменная в конце основного цикла)
	float start = clock();

	FallingObject box(5, 10, box_texture);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{

		//Счетчик FPS
		tmp2 = time(NULL);
		if (tmp2 - tmp1 >= 1)
		{
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
			tmp1 = tmp2;
		}

		fps += 1;

		//----Переменные для перемещения----

		//Переменная для перемещения влево-вправо
		int dx(0);


		

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();

			//Проверяем нажатия
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)
				{
					dx = -7;
				}
				else
				{
					if (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)
					{
						dx = 7;
					}
				}

				if (event.key.code == Keyboard::W || event.key.code == Keyboard::Up || event.key.code == Keyboard::Space)
				{
					ball.jump();
				}
			}
		}


		
		
		
		
		
		
		//----Перемещение----
		
		box.fall();
		ball.fall();
		ball.move(dx, 0);
		ball_sprite.setPosition(ball.getPosition().first, ball.getPosition().second);

		//----Коллизии----

		//Низ
		
		if (ball_sprite.getGlobalBounds().intersects(border_vertical_sprite.getGlobalBounds()))
		{
			ball.landing();
			ball.cancelMove(0, 1, border_vertical_sprite);
			ball_sprite.setPosition(ball.getPosition().first, ball.getPosition().second);
		}

		if (box.isOverlap(border_vertical_sprite))
		{
			box.landing();
		}
		

		//Пишем в мяч окончательные координаты

		float end = clock();

		ball.finalThisFrame((end - start) / 1000);
		
		start = end;

		//


		//----ОТРИСОВКА----


		window.clear(Color::Blue);

		window.draw(background_sprite);

		window.draw(border_vertical_sprite);
		window.draw(border_horizontal_l_sprite);
		window.draw(border_horizontal_r_sprite);
		window.draw(ball_sprite);

		box.draw(window);

	

		// Отрисовка окна	
		window.display();

		//Регулировка скорости потока
		float frame_duration = loop_timer.getElapsedTime().asMilliseconds();
		float time_to_sleep = int(1000.f / wanted_fps) - frame_duration;
		if (time_to_sleep >= 0) 
		{
			sf::sleep(sf::milliseconds(time_to_sleep));
		}
		loop_timer.restart();
	}

	return 0;
}