#pragma once
#include <SFML/Graphics.hpp>
#include "object.h"
#include <time.h>
#include <cstdlib>

#include <thread>

#include "collisions.h"

//���������� ���������� � �������

float wanted_fps(100); //FPS


vector<Object*> allObjects;

//���
Texture ball_texture;

//���������
Texture
border_horizontal_texture,
border_vertical_texture,
background_texture;


//�������� �������
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

Clock sfml_clock; //���� sfml, ����������� ������ ����
Clock globalTime; //� ��� �� �����������

float global_time; //� ��� �� ����������

//RenderWindow window(VideoMode(800, 600), "Game");


//void draw_all();