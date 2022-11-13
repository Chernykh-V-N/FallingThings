#pragma once
#include <SFML/Graphics.hpp>
#include "object.h"
#include <time.h>
#include <cstdlib>

#include <thread>

#include "collisions.h"

//√лобальные переменные и объекты

float wanted_fps(100); //FPS


vector<Object*> allObjects;

//ћ€ч
Texture ball_texture;

//ќкружение
Texture
border_horizontal_texture,
border_vertical_texture,
background_texture;


//ѕадающие объекты
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

Clock sfml_clock; //часы sfml, обновл€ютс€ каждый кадр
Clock globalTime; //а эти не обновл€ютс€

float global_time; //а это их переменна€

//RenderWindow window(VideoMode(800, 600), "Game");


//void draw_all();