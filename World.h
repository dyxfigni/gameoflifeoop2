#pragma once
#include "Point.h"
#include <iostream>
#include <vector>
#include <map>

#define WIDTH 40 // ��������� ��� ������� ���� � ������
#define HEIGHT 20// ��������� ��� ������� ���� � ������
#define WORLDS 10  // ���������� ����� ��� ���������� ���������� ������������

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

	// ������� ���� ����� ������
	void countLive();
	// ������� ������� ��� ������ ������ 
	void countNei(Point &pos, std::vector<Point>& coordinatesEatableNei, std::map<Tage, int>& numOfNeighborsByTags, int &k);

	// ��������� ��������� ��������� �� ������ �������� 
	//������ ��� �������: ���� ���������� ������� ���������, 
	//�� ������ �������� ����, ��� - �������
	void nextGen();

	// ����� ���� �� �����
	void out();

	// ��������� ����������� � ���������� ���� 
	//int compare(Point world[WIDTH][HEIGHT], Point oldWorld[WIDTH][HEIGHT]);

	int compare(World oldWorld);
};

class StabConf
{
public:
	World worlds[WORLDS];
	//std::vector<World> worlds;

	//����������� �������� ���� � ������ ������������ �����
	//void cmpWorldForKonfs(World& worldTek, int& cycles);
	int stabilConf(World& world, int& cycles);
};