#pragma once
/* информация о клетках в мире хранится в переменной world типа поинт для того, чтобы понимать
жива ли она или нет
*/

enum Tage
{
	TAGE_Plant, // 
	TAGE_Fitofag, // ест растения и рассыпает их
	TAGE_Geterotrof // ест травоядных 
};

//enum Color
//{
//	Green, // растения 
//	Yellow,// фитофаг
//	Pink // атротроф
//};

class Point// клетки, если живы, то - 1, если нет - 0, 1 - "#", 0 " " 
{	
protected:
	bool isLive = 1; 
	// 0 - растение, 1 - травоядный, 2 - хищник
	Tage tage;
public:
	int x = 0;
	int y = 0;

	inline bool getIsLive() const { return isLive; }
	inline Tage getTage() const { return tage; }
	inline void setIsLive(bool live) { this->isLive = live; }

	virtual void Eat(Point p)
	{
		;
	}
};

class Plant : public Point
{
public:
	Plant()
	{
		isLive = 1;
		tage = TAGE_Plant;
	}

	void Eat(Point p) override
	{
		switch (p.getTage())
		{
		case TAGE_Plant:
			break;
		case TAGE_Fitofag:		
			break;
		case TAGE_Geterotrof:
			//p.setIsLive(0);
			break;
		default:
			break;
		}
	}
};

class Fitofag : public Point
{
public:
	Fitofag()
	{
		isLive = 1;
		tage = TAGE_Fitofag;
	}
	void Eat(Point p) override
	{
		switch (p.getTage())
		{
		case TAGE_Plant:
			p.setIsLive(0);
			break;
		case TAGE_Fitofag:

			break;
		case TAGE_Geterotrof:
			
			break;
		default:
			break;
		}
	}
};

class Geterotrof : public Point
{
public:
	Geterotrof()
	{
		isLive = 1;
		tage = TAGE_Geterotrof;
	}
	void Eat(Point p) override
	{
		switch (p.getTage())
		{
		case TAGE_Plant:
			//isLive = 0;
			break;
		case TAGE_Fitofag:
			p.setIsLive(0);
			break;
		case TAGE_Geterotrof:

			break;
		default:
			break;
		}
	}
};