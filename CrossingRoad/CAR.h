#pragma once
#include "VEHICLE.h"

const int INCar_PosX[] = { 0, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7};
const int INCar_PosY[] = { 0, 0, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0};

class Car :	public Vehicle
{
	static int stepCar;
public:
	Car(int x, int direction) : Vehicle(x, direction)
	{}

	static void nhayStep(int lv)
	{
		stepCar--;
		if (stepCar < 0) stepCar = (NHIPCAR - lv) > 0 ? (NHIPCAR - lv) : 0;
	}
	bool Left()
	{
		if (stepCar == 0)
		{
			m_x--;
			return 1;
		}
		return 0;
	}
	bool Right()
	{
		if (stepCar == 0)
		{
			m_x++;
			return 1;
		}
		return 0;
	}
	bool FinishLane()
	{
		if (m_direction == DIRECTION_LEFT)
		{
			if (m_x <= BEGINCONSOLEWIDTHPIXELGAME - 1 - WIDTHOFCAR) return 1;
			return 0;
		}
		else
		{
			if (m_x >= WIDTHPIXELNUMBER + 1) return 1;
			return 0;
		}
	}
	bool impactHuman(int car_y, int hm_x, int hm_y)
	{
		if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFCAR
			|| car_y <= hm_y - HEIGHTOFMAN || car_y >= hm_y + HEIGHTOFCAR)
		{
			return 0;
		}
		else
		{
			for (int i = 0, j; i < WIDTHOFMAN; i++)
			{
				for (j = 0; j < 12; j++)
				{
					if (hm_x + INHuman_PosX[i] == m_x + INCar_PosX[j]
						&& hm_y + INHuman_PosY[i] == car_y + INCar_PosY[j])
						return 1;
				}
			}
			return 0;
		}
	}
	void In(int car_y) // y chính xác là vị trí xe
	{
		if (m_x >= BEGINCONSOLEWIDTHPIXELGAME && m_x <= WIDTHPIXELNUMBER - 1 - 7)
		{

			ToMau(m_x, car_y, (char *)"        ", CARCOLOR);
			ToMau(m_x + 2, car_y - 1, (char *)"    ", CARCOLOR);
		}
		else
		{
			for (int i = 0; i < 12; i++)
				ToMau(m_x + INCar_PosX[i], car_y + INCar_PosY[i], ' ', CARCOLOR);
		}
	}
	void InSoftlyLeft(int car_y) // y chính xác là vị trí xe
	{
		if(m_x % 2 == 0) ToMau(m_x + 6, car_y - 1, '_', VACHROADCOLOR);
		else ToMau(m_x + 6, car_y - 1, ' ', VACHROADCOLOR);
		ToMau(m_x + 8, car_y, ' ', ROADCOLOR);
		ToMau(m_x + 2, car_y - 1, ' ', CARCOLOR);
		ToMau(m_x + 0, car_y, ' ', CARCOLOR);
	}
	void InSoftlyRight(int car_y) // y chính xác là vị trí xe
	{
		ToMau(m_x + 5, car_y - 1, ' ', CARCOLOR);
		ToMau(m_x + 7, car_y, ' ', CARCOLOR);
		if(m_x % 2 == 1) ToMau(m_x + 1, car_y - 1, '_', VACHROADCOLOR);
		else ToMau(m_x + 1, car_y - 1, ' ', VACHROADCOLOR);
		ToMau(m_x - 1, car_y, ' ', ROADCOLOR);
	}
};

