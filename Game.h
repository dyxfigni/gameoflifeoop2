#pragma once
#include "Menu.h"
#include "World.h"
#include <iomanip>
#include <fstream>
#include <ctime>
#include <iostream>
#include <algorithm>

class Game
{
public:
	int index = 0;// количетсво циклов 
	int takt = 0; 
	int gameTime = 0; // время
	bool optimastabil = 0;
	int numLivingCells = 0;
	int prefTime = 0;
	//int cellsNum = 0;
	int dlitelnost = 100000;
	int taktyIgry = 100000;

	// сохранение 
	void save();
	// загрузка файла
	void load();

	//конец игры
	//int end();

	//логика игры
	void game();

	//настройка
	void preferences();

	void rules();

	int run();

	
};

