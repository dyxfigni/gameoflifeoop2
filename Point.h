#pragma once
/* ���������� � ������� � ���� �������� � ���������� world ���� ����� ��� ����, ����� ��������
���� �� ��� ��� ���
*/

enum Tage
{
	TAGE_Plant, // 
	TAGE_Fitofag, // ��� �������� � ��������� ��
	TAGE_Geterotrof // ��� ���������� 
};

//enum Color
//{
//	Green, // �������� 
//	Yellow,// �������
//	Pink // ��������
//};

class Point// ������, ���� ����, �� - 1, ���� ��� - 0, 1 - "#", 0 " " 
{	
protected:
	bool isLive = 1; 
	// 0 - ��������, 1 - ����������, 2 - ������
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