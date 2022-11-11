#include <SFML/Graphics.hpp>
#include "object.h"
#include <time.h>
#include <cstdlib>

#include "collisions.h"

/*
#include <box2d/box2d.h>
#include <box2d/b2_world.h>

#pragma comment(lib,"Box2D.lib")
*/
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-system.lib")


using namespace sf;



//Глобальные переменные и объекты

float wanted_fps(100); //FPS


vector<Object*> allObjects;

//Мяч
Texture ball_texture;

//Окружение
Texture
	border_horizontal_texture,
	border_vertical_texture,
	background_texture;


//Падающие объекты
Texture
	box_texture,
	barrell_texture,
	brick_texture,
	fridge_texture,
	microwave_texture,
	oven_texture,
	toilet_texture,
	tv_texture,
	wardrobe_texture,
	washing_texture;

vector<Object*> falling_objects;
vector<Object*> borders;

Clock sfml_clock; //часы sfml, обновляются каждый кадр
Clock globalTime; //не обновляются

float global_time;


int main()
{
	//Таймер для регулировки скорости работы
	sf::Clock loop_timer;

	
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "SFML Works!");

	//Счетчик FPS
	int fps(250);

	time_t tmp1, tmp2;
	tmp1 = time(NULL);


	

	//Рандом
	srand(time(NULL));

	//Переменные для езды
	float dx;
	float dy;


	//----ТЕКСТУРЫ----

	//Мяч
	ball_texture.loadFromFile("Graphics\\Ball_1.png");

	//Окружение
	border_horizontal_texture.loadFromFile("Graphics\\border_horizontal.png");
	border_vertical_texture.loadFromFile("Graphics\\border_vertical.png");
	background_texture.loadFromFile("Graphics\\background_1.png");

	//Падающие объекты

	box_texture.loadFromFile("Graphics\\Box.png");
	barrell_texture.loadFromFile("Graphics\\Barrell.png");
	brick_texture.loadFromFile("Graphics\\Brick.png");
	fridge_texture.loadFromFile("Graphics\\Fridge.png");
	microwave_texture.loadFromFile("Graphics\\Microwave.png");
	oven_texture.loadFromFile("Graphics\\Oven.png");
	toilet_texture.loadFromFile("Graphics\\Toilet.png");
	tv_texture.loadFromFile("Graphics\\TV.png");
	wardrobe_texture.loadFromFile("Graphics\\Wardrobe.png");
	washing_texture.loadFromFile("Graphics\\Washing.png");

	vector<Texture> falling_objects_textures
	{
		box_texture,
		barrell_texture,
		brick_texture,
		fridge_texture,
		microwave_texture,
		oven_texture,
		toilet_texture,
		tv_texture,
		wardrobe_texture,
		washing_texture
	};

	loadTextures(falling_objects_textures);

	Object background(Vector2f(400, 300), background_texture);
	Object* border_horizontal_l = new Object(Vector2f(5, 300), border_horizontal_texture);
	Object* border_horizontal_r = new Object(Vector2f(795, 300), border_horizontal_texture);
	Object* border_vertical = new Object(Vector2f(400, 595), border_vertical_texture);
	Object* not_border_but_wardrobe = new Object(Vector2f(200, 250), wardrobe_texture, 5);

	borders.push_back(border_horizontal_l);
	borders.push_back(border_horizontal_r);
	borders.push_back(border_vertical);
	borders.push_back(not_border_but_wardrobe);

	Player player_ball(Vector2f(400, 0), ball_texture);

	Player test_object(Vector2f(300, 300), ball_texture, 1, 0.7);

	Object not_border_but_washing_machine(Vector2f(500, 300), washing_texture, 10);


	//Таймер для просчета физики(вторая переменная в конце основного цикла)
	global_time = globalTime.getElapsedTime().asMilliseconds(); //эту переменную юзаем для физики. 
	float update_time;
	float time_buffer;

	//Переменная для рандома
	int random_line(0);

	//----ГЛАВНЫЙ ЦИКЛ----
	
	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//Таймер для скорости работы программы
		float p_time = sfml_clock.getElapsedTime().asMilliseconds();
		p_time /= 1000;
		sfml_clock.restart();

		/*
		//Спавн предметов
		random_line = rand() % 1000;
		if (random_line < 7)
		{
			cout << "Spawn object" << endl;
			falling_objects.push_back(new Object(spawnObject(random_line)));
		}
		*/

		//Счетчик FPS
		tmp2 = time(NULL);
		if (tmp2 - tmp1 >= 1)
		{
			std::cout << "FPS: " << fps << std::endl;
			fps = 0;
			tmp1 = tmp2;
		}

		fps += 1;

		dx = 0;//переменная езды
		dy = 0;

		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}


		//----Клавиатура----
		if(Keyboard::isKeyPressed(Keyboard::W))
		{
			player_ball.jump();
			dy = -70;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dx = -70;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dy = 70;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dx = 70;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			not_border_but_washing_machine.useImpulse(Vector2f(0, -10));

			player_ball.jump();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			dx = -70;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			dx = 70;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			//not_border_but_washing_machine.useImpulse(Vector2f(-3, 0));
			player_ball.jump();
			dy = -70;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			dy = 70;
		}

		//----МЕХАНИКА----

		player_ball.move(Vector2f(dx * p_time, 0));
		/*
		for (auto i : borders)
		{
			if (CircleVsAABB(player_ball.getCircle(), i->getAABB()))
			{
				cout << "Collision" << endl;
			}
		}
		*/

		test_object.resetForce();
		//test_object.useForce(Vector2f(0, 30));
		test_object.useForce(Vector2f(0, dy));
		test_object.useForce(Vector2f(dx, 0));

		
		//---Коллизии---
		/*
		for (auto i : borders)
		{
			//if (AABBvsAABB(test_object.getAABB(), i->getAABB()))
			//{
				if(CircleVsAABB(test_object.getCircle(), i->getAABB()))
				{
					cout << "Collision sprites" << endl;
				}
				//cout << "Collision AABB" << endl;
			//}
		}
		*/

		/*
		if (CircleVsAABB(test_object.getCircle(), not_border_but_washing_machine.getAABB()))
		{
			cout << "Collision" << endl;
			not_border_but_washing_machine.useImpulse(test_object.getImpulse());
		}
		*/

		collision(test_object, not_border_but_washing_machine);

		//---Время кадра для физики---

		time_buffer = globalTime.getElapsedTime().asMilliseconds();
		update_time = time_buffer - global_time;
		global_time = time_buffer;

		//----ОТРИСОВКА----

		window.clear(Color::Blue);

		background.draw(window, update_time);

		
		for (auto i : borders)
		{
			i->draw(window, update_time);
		}
		not_border_but_washing_machine.draw(window, update_time);

		test_object.draw(window, update_time);
		
		/*
		for (auto i : falling_objects)
		{
			i->move(Vector2f(0, 30 * p_time));
			i->draw(window);
		}
		*/

		player_ball.draw(window, update_time);
		
		// Отрисовка окна	
		window.display();


		/*
		//Регулировка скорости потока
		float frame_duration = loop_timer.getElapsedTime().asMilliseconds();
		float time_to_sleep = int(1000.f / wanted_fps) - frame_duration;
		if (time_to_sleep >= 0)
		{
			sf::sleep(sf::milliseconds(time_to_sleep));
		}
		loop_timer.restart();
		*/
	}

	return 0;
}