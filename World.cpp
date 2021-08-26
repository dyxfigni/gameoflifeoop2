#include "World.h"
#include "myFunc.h"
#include <vector>
#include <map>

World::World()
{	
	world = new Point*[HEIGHT]; 
	for (size_t i = 0; i < HEIGHT; i++)
	{		
		world[i] = new Point[WIDTH];
		//world[i] = nullptr;
	}

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			/*щий правый операнд типа "int" (или приемлемое преобразование отсутствует)
			*/
			world[i][j].x = i;
			world[i][j].y = j;
			int num = rand() % 10000;

			Point* p = new Point;
			switch (rand() % 3)
			{
			case 0:
				p = new Plant;
				break;
			case 1:
				p = new Fitofag;
				break;
			case 2:
				p = new Geterotrof;
				break;
			default:
				break;
			}		
			if (num % 2 == 0)
			{
				p->setIsLive(1);
				world[i][j] = *p;
			}
			else
			{
				p->setIsLive(0);
				world[i][j] = *p;
			}
		}
	}
}

//World::World(int cells)
//{
//	if (cells == 0)
//	{
//		World();
//		return;
//	}
//	world = new Point * [HEIGHT];
//	for (size_t i = 0; i < HEIGHT; i++)
//	{
//		world[i] = new Point[WIDTH];
//		//world[i] = nullptr;
//	}
//
//	int k = 0;
//	for (size_t i = 0; i < HEIGHT; i++)
//	{
//		for (size_t j = 0; j < WIDTH; j++)
//		{
//			world[i][j].x = i;
//			world[i][j].y = j;
//			int num = rand() % 10000;
//			Point* p = new Point;
//			switch (rand() % 3)
//			{
//			case 0:
//				p = new Plant;
//				break;
//			case 1:
//				p = new Fitofag;
//				break;
//			case 2:
//				p = new Geterotrof;
//				break;
//			default:
//				break;
//			}
//			if (num % 2 == 0)
//			{
//				if (k < cells)
//				{
//					p->setIsLive(1);
//					world[i][j] = *p;
//					k++;
//				}
//				else
//				{
//					p->setIsLive(0);
//					world[i][j] = *p;
//				}
//			}
//			else
//			{
//				p->setIsLive(0);
//				world[i][j] = *p;
//			}
//		}
//	}
//}

World::World(const World& oldWorld)
{
	world = new Point * [HEIGHT];
	for (size_t i = 0; i < HEIGHT; i++)
	{
		world[i] = new Point[WIDTH];
		//world[i] = nullptr;
	}

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			this->world[i][j] = oldWorld.getPoint(i, j);
		}
	}
}

World& World::operator=(const World& world)
{
	if (this == &world)
		return *this;

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			this->world[i][j] = world.getPoint(i, j);
		}
	}

	return *this;
}


Point World::getPoint(int x, int y) const
{
	return world[x][y];
}

void World::countLive()
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (world[i][j].getIsLive() == 1)
			{
				switch (world[i][j].getTage())
				{
				case TAGE_Plant:
					livingPlants++;
					break;
				case TAGE_Fitofag:
					livingFitofags++;
					break;
				case TAGE_Geterotrof:
					livingGeterotrof++;
					break;
				default:
					break;
				}				
			}
		}
	}
}

void World::countNei(Point &pos, std::vector<Point>& coordinatesEatableNei, std::map<Tage, int>& numOfNeighborsByTags, int &k)
{
	// считать соседние клетки по Муру
	Point moor;
	moor.x = pos.x - 1;
	moor.y = pos.y - 1;
	// pos - данная клетка 
	Tage tage = world[pos.x][pos.y].getTage();
	for (int i = moor.x; i < moor.x + 3; i++)
	{
		for (int j = moor.y; j < moor.y + 3; j++)
		{
			int x = i;
			int y = j;
			//меньше размера

			// диагонали
			if (i == -1 && j == -1)
			{
				i = HEIGHT - 1;
				j = WIDTH - 1;
			}
			else if (i == WIDTH && j == HEIGHT)
			{
				i = 0;
				j = 0;
			}
			// вверх есть
			else if (i == -1)
			{			
				if (j == WIDTH)
				{			
					i = HEIGHT - 1;
					j = 0;
				}			
				i = HEIGHT - 1;
			}
			//право есть
			else if (j == WIDTH)
			{
				if (i == HEIGHT)
				{
					i = 0;
					j = 0;
				}
				j = 0;
			}
			// лево есть 
			else if(j == -1)
			{
				if (i == HEIGHT)
				{
					i = 0;
					j = WIDTH - 1;
				}
				j = WIDTH - 1;
			}
			//низ есть
			else if(i == HEIGHT)
			{
				if (j == WIDTH)
				{
					i = 0;
					j = 0;
				}
				i = 0;		
			}
			switch (tage)
			{
			case TAGE_Plant:
				if (world[i][j].getTage() == TAGE_Geterotrof)
				{
					coordinatesEatableNei.push_back(world[i][j]);
				}
				break;
			case TAGE_Fitofag:
				if (world[i][j].getTage() == TAGE_Plant)
				{
					coordinatesEatableNei.push_back(world[i][j]);
				}
				break;
			case TAGE_Geterotrof:
				if (world[i][j].getTage() == TAGE_Fitofag)
				{
					coordinatesEatableNei.push_back(world[i][j]);
				}
				break;
			default:
				break;
			}

			switch (world[i][j].getTage())
			{
			case TAGE_Plant:
				numOfNeighborsByTags[TAGE_Plant]++;
				break;
			case TAGE_Fitofag:
				numOfNeighborsByTags[TAGE_Fitofag]++;
				break;
			case TAGE_Geterotrof:
				numOfNeighborsByTags[TAGE_Geterotrof]++;
				break;
			default:
				break;
			}

			if (world[i][j].getIsLive() == 1)
			{
				k++;
			}
			i = x;
			j = y;
		}
	}	
}

//void World::nextGen()
//{
//	for (size_t i = 0; i < HEIGHT; i++)
//	{
//		for (size_t j = 0; j < WIDTH; j++)
//		{
//			Point pos;
//			pos.x = i;
//			pos.y = j;
//			int k = this->countNei(pos); // количество соседей
//			Point tmp;
//			if (this->world[i][j].getIsLive() == 1)
//			{
//				if (k < 2 || k > 3)
//				{
//					this->world[i][j].setIsLive(0);
//				}
//				else
//				{
//					this->world[i][j].setIsLive(1);
//				}
//			}
//			else
//			{				
//				if (k == 3)
//				{
//					this->world[i][j].setIsLive(1);
//				}
//			}
//		}
//	}
//}

void World::nextGen()
{
	livingPlants = 0;
	livingFitofags = 0;
	livingGeterotrof = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			Point pos;
			pos.x = i;
			pos.y = j;
			int k = 0;
			
			std::vector<Point> coordinatesEatableNei; // вектор съедобных клеток

			// контейнер с информацией о количестве соседей, рассортированных по тегу
			std::map<Tage, int> numOfNeighborsByTags = { { TAGE_Plant, 0}, 
													     { TAGE_Fitofag, 0},
													     { TAGE_Geterotrof, 0}}; 

			this->countNei(pos, coordinatesEatableNei, numOfNeighborsByTags,k); // количество соседей
			Point*tmp = new Point;


			if (this->world[i][j].getIsLive() == 1) // живой
			{
				if (coordinatesEatableNei.size() != 0)
				{
					k = rand() % coordinatesEatableNei.size();
					world[i][j].Eat(coordinatesEatableNei[k]);
				}					
				switch (world[i][j].getTage())
				{
				case TAGE_Plant:
					if (numOfNeighborsByTags[TAGE_Plant] >= 4)
						this->world[i][j].setIsLive(0);
					break;
				case TAGE_Fitofag:
					if (numOfNeighborsByTags[TAGE_Plant] > 2)
					{
						tmp = new Fitofag;
						world[i][j] = *tmp;
					}
					break;
				case TAGE_Geterotrof:
					if(numOfNeighborsByTags[TAGE_Fitofag] > 3)
					{
						tmp = new Geterotrof;
						world[i][j] = *tmp;
					}
					break;
				default:
					break;
				}

				if (k < 2 || k > 4)
				{
					this->world[i][j].setIsLive(0);
				}
				else
				{
					this->world[i][j].setIsLive(1);
				}
			}
			else // мертвый
			{ 
				int chance = (double)rand() / (double)RAND_MAX;

				//if (world[i][j].getTage() == TAGE_Geterotrof) // если труп гететеротрофа
				//{
				//	// на месте трупа появляется растение
				//	tmp = new Plant;
				//	world[i][j] = *tmp;
				//}
				switch (world[i][j].getTage())
				{
				/*case TAGE_Plant:
					if (chance > (double)rand() / (double)RAND_MAX)
					{
						tmp = new Fitofag;
						world[i][j] = *tmp;
					}
					break;*/
				case TAGE_Fitofag:
					if (chance > (double)rand() / (double)RAND_MAX)
					{
						tmp = new Plant;
						world[i][j] = *tmp;
					
					}
					break;	
				case TAGE_Geterotrof:
					if (chance > 0.2)
					{
						tmp = new Plant;
						world[i][j] = *tmp;
					}
					break;
				default:
					break;
				}
				if (k == 3)
				{
					this->world[i][j].setIsLive(1);
				}
			}
		}
	}
}

void World::out()
{
	system("cls"); 
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (world[i][j].getIsLive() != 1) 
				std::cout << " ";
			else
			{
				switch (world[i][j].getTage())
				{
				case TAGE_Plant:
					SetColor(2, 0);
					std::cout << "#";
					SetColor(8,0);
					break;
				case TAGE_Fitofag:
					SetColor(14, 0);
					std::cout << "#";
					SetColor(8, 0);
					break;
				case TAGE_Geterotrof:
					SetColor(5, 0);
					std::cout << "#";
					SetColor(8, 0);
					break;

				default:
					SetColor(8, 0);
					std::cout << "#";
					SetColor(8, 0);
					break;
				}			
			}
		}
		std::cout << std::endl;
	}
}

int World::compare(World oldWorld)
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (this->world[i][j].getIsLive() != oldWorld.getPoint(i, j).getIsLive())
				return -1;
		}
	}
	return 0;
}

int StabConf::stabilConf(World& worldPres, int& cycles)
{
	for (size_t i = 0; i <= cycles; i++)
	{
		if (worldPres.compare(worlds[i]) == 0)
		{
			return 0;
		}
	}
	return -1;
}
