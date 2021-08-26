#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

using namespace std;

void Game::save()
{
	ofstream out("saves.txt", ios::app);
	time_t now = time(0);
	char* dt = ctime(&now);
	std::string line;
	(optimastabil == 1) ? line = " да" : line = " нет";
	if (out.is_open())
	{
		out << dt <<
			" Время: " << gameTime <<
			" Живые клетки: " << numLivingCells <<
			" Количество тактов: " << takt <<
			"\n" <<
			" Стабильная конфигурация: " << line <<
			"." << endl;
	}
	out.close();
}

void Game::load()
{
	system("cls");
	gotoxy(0, 0);
	cout << "	______________MMMMMMMMMMMMM " << endl;
	cout << "	_____________MMMMMMMMMMMMMMMM" << endl;
	cout << "	____________MMMMMMMMMMMMMMMMMM" << endl;
	cout << "	___________MMM____MMMMMMMMMMMMMMMM" << endl;
	cout << "	___________MM______MMMMMMMMMMMMMMM" << endl;
	cout << "	___________MM_____MMMMMMMMMMMMMMMMM" << endl;
	cout << "	____________MM___MMMMMMMMMMMMMMMMM" << endl;
	cout << "	_____________MMMMMMMMMMMMMMMMMMMM" << endl;
	cout << "	______________MMMMMMMMMMMMMMMMM" << endl;
	cout << "	____MMMMM______MMMMMMMMMMMMMM_____MMMMMM" << endl;
	cout << "	__MMMMMMMMMM_____MMMMMMMMMM____MMMMMMMMMMM" << endl;
	cout << "	_MMMM_____MMMMMM___MMMMMM___MMMMMMMMMMMMMMM" << endl;
	cout << "	_MMM______MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl;
	cout << "	_MMM_MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl;
	cout << "	_MMMMMMMMMMMMMMMMMMMMMMMMM_MMMMMMMMMMMMMMMM" << endl;
	cout << "	__MMMMMMMMMMMMMMMMMMMM__MM___MMMMMMMMMMMMM" << endl;
	cout << "	_____MMMMMMMMMMMMMMM_M__MMM_____MMMMMMM" << endl;
	cout << "	_____MMMMMMMMMMMMMM__M___MMM______MMMMM" << endl;
	cout << "	_____MMMMMMMMMMMMM___MM___MM_______MMMMM" << endl;
	cout << "	_____MMMMMMMMMMMM____MMM____MMM_____MMM" << endl;
	cout << "	______MMMMMMMMMM_____MMMM____MMMMMMMMM" << endl;
	cout << "	________MMMMMM________MMMM_____MMMMM" << endl;
	cout << "	_________________________MM" << endl;
	std::string line;
	char buff[11];
	ifstream in("saves.txt");
	if (in.is_open())
	{
		int k = 0;
		while (getline(in, line))
		{
			gotoxy(55, k);
			k++;
			std::cout << line << std::endl;
			k++;
		}
	}
	in.close();
	system("pause");
}

void Game::rules()
{
	system("cls");	
	gotoxy(0, 0);
	cout << "Есть 3 вида клеток: растения(автотрофы), травоядные и хищники. Когда умирают животные(гетеротрофы), то на их месте могут появится растения, чем больше вокруг растений, тем больше травоядных, чем больше травоядных, тем больше хищников \n\n";
	system("pause");
}
//
//int Game::end()
//{
//	optimastabil = 0;
//	takt = 0;
//	cout << "Записать результат?" << endl;
//	Menu res;
//	vector <string> textres = {
//		"Да",
//		"Нет"
//	};
//	int numres = res.select_vertical(textres, 1, 23);
//	switch (numres)
//	{  
//	case 0:
//		system("cls");
//		save();
//		return 1;
//	default:
//		return 1;
//	}
//}


void Game::game()
{
	auto endToSave = [this]()->void {
		this->optimastabil = 0;
		this->takt = 0;
		cout << "Записать результат?" << endl;
		Menu res;
		vector <string> textres = {
			"Да",
			"Нет"
		};
		int numres = res.select_vertical(textres, 1, 23);
		switch (numres)
		{
		case 0:
			system("cls");
			this->save();
		default:
			break;
		}
	};

	
	
	World world;
		
	StabConf stabUniverse; // массив миров
	Sleep(400);
	
	do
	{
		if (_kbhit() == 0)
		{	
			world.out();
			World oldWorld = world;
			stabUniverse.worlds[this->index] = world;
			world.nextGen(); // текущая конфигурация превращается в следующею			
			world.out();
			world.countLive();
			numLivingCells = world.livingFitofags + world.livingPlants + world.livingGeterotrof;
			gameTime = clock() / CLOCKS_PER_SEC - prefTime;// время 
			cout << "Время:" << setw(3) << gameTime << setw(3) << fixed << setprecision(2) << "Живые клетки: " << setw(3) << numLivingCells << fixed << setprecision(2) << "Такт: " << takt;
			cout << "Растений: " << setw(3) << world.livingPlants << setw(3) << fixed << setprecision(2) << "Травоядных" << world.livingFitofags << setw(3) << fixed << setprecision(2) << "Хищников" << world.livingGeterotrof;
			Sleep(400);

			if (world.compare(oldWorld) == 0)
				endToSave();

			// сравнивание текущей конфигурации с массивом миров
			if (stabUniverse.stabilConf(world, index) == 0)
			{
				cout << "Стабильная система!";
				cout << endl;
				optimastabil = 1;
			}
			if (index < WORLDS)
			{
				index++;
				takt++;
			}
			if (index == WORLDS)
				index = 0;
			
		}
		else
		{
			cout << endl << "Пауза" << endl;
			do
			{
				Menu start;
				vector <string> textmenu1 = {
					"Продолжить",
					"Выход"
				};
				int num = start.select_vertical(textmenu1, 1, 23);
				switch (num)
				{
				case 0:
					continue;
				default:
					cout << "Записать результат?" << endl;
					Menu res;
					vector <string> textres = {
						"Да",
						"Нет"
					};
					int numres = start.select_vertical(textres, 1, 28);
					switch (numres)
					{
					case 0:
						system("cls");
						save();
					default:
						return;
					}
				}
			} while (_kbhit() != 0);// пока не будет нажата кнопка 
		}
	} while (optimastabil != 1
		&& gameTime != dlitelnost
		&& takt != taktyIgry
		&& numLivingCells != 0);
	//stabUniverse[WORLDS] = cleanUni(stabUniverse);
	endToSave();
}

void Game::preferences()
{
	system("cls");
	cout << "0 - бесконечно" << endl;
	cout << "Длительность: ";
	cin >> dlitelnost;
	cout << "Количество тактов: ";
	cin >> taktyIgry;
	if (dlitelnost == 0 || takt == 0)
	{
		dlitelnost = 100000;
		taktyIgry = 100000;
	}
	/*cout << "Введите количество клеток, рекомендовано от 300, 0 - по умолчанию: ";
	cin >> cellsNum;
	if (cellsNum > WIDTH * HEIGHT)
	{
		do
		{
			cout << "Введите значение меньше чем " << WIDTH * HEIGHT << " ";
			cin >> cellsNum;
		} while (cellsNum > WIDTH * HEIGHT);
	}*/
	prefTime = clock() / CLOCKS_PER_SEC;

	this->game();
}

int Game::run()
{
	do
	{
		system("cls");
		//void flower();
		Menu start;
		vector <string> textmenu1 = {
			"Начать симуляцию",
			"Результаты",
			"Правила",
			"Выход"
		};
		int num = start.select_vertical(textmenu1, 40, 4);
		switch (num)
		{
		case 0:
			preferences();
			break;
		case 1:
			load();
			break;
		case 2:
			rules();
			break;
		default:
			return 0;
		}
	} while (true);
}
