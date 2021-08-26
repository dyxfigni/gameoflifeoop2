#pragma once
#include "Point.h"
#include <iostream>
#include <vector>
#include <map>

#define WIDTH 40 // константы для размера поля в высоту
#define HEIGHT 20// константы для размера поля в ширину
#define WORLDS 10  // количество миров для нахождения стабильной конфигурации

class World
{
public:
	Point** world;

	//int cellsLiving;
	int livingPlants = 0;
	int livingFitofags = 0;
	int livingGeterotrof = 0;
	World();
	//World(int);
	World(const World& world);
	World& operator=(const World& world);

	Point getPoint(int x, int y) const;

	// считать всех живых клеток
	void countLive();
	// считать соседей для каждой клетки 
	void countNei(Point &pos, std::vector<Point>& coordinatesEatableNei, std::map<Tage, int>& numOfNeighborsByTags, int &k);

	// следующее поколение создается на основе проверки 
	//правил для старого: если количество соседей правильна, 
	//то клетка остается жить, нет - умерает
	void nextGen();

	// вывод поля на экран
	void out();

	// сравнение предыдущего и настоящего мира 
	//int compare(Point world[WIDTH][HEIGHT], Point oldWorld[WIDTH][HEIGHT]);

	int compare(World oldWorld);
};

class StabConf
{
public:
	World worlds[WORLDS];
	//std::vector<World> worlds;

	//копирование текущего мира в массив конфигураций миров
	//void cmpWorldForKonfs(World& worldTek, int& cycles);
	int stabilConf(World& world, int& cycles);
};