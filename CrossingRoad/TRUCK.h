#pragma once
#include "VEHICLE.h"

const int INTruckMoveRight_PosX[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7 };
const int INTruckMoveRight_PosY[] = { 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0 };

const int INTruckMoveLeft_PosX[] = { 0, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 };
const int INTruckMoveLeft_PosY[] = { 0, 0, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1};

class Truck :	public Vehicle
{
	static int stepTruck;
public:
	Truck(int x, int direction) : Vehicle(x, direction)
	{}

	static void nhayStep(int lv)
	{
		stepTruck--;
		if (stepTruck < 0) stepTruck = (NHIPTRUCK - lv) > 0 ? (NHIPTRUCK - lv) : 0;
	}
	bool Left()
	{
		if (stepTruck == 0)
		{
			m_x--;
			return 1;
		}
		return 0;
	}
	bool Right()
	{
		if (stepTruck == 0)
		{
			m_x++;
			return 1;
		}
		return 0;
	}
	bool impactHuman(int truck_y, int hm_x, int hm_y)
	{
		if (m_direction == DIRECTION_LEFT)
		{
			if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFTRUCK
				|| truck_y <= hm_y - HEIGHTOFMAN || truck_y >= hm_y + HEIGHTOFTRUCK)
			{
				return 0;
			}
			else
			{
				for (int i = 0, j; i < WIDTHOFMAN; i++)
				{
					for (j = 0; j < 14; j++)
					{
						if (hm_x + INHuman_PosX[i] == m_x + INTruckMoveLeft_PosX[j]
							&& hm_y + INHuman_PosY[i] == truck_y + INTruckMoveLeft_PosY[j])
							return 1;
					}
				}
				return 0;
			}
		}
		else
		{
			// Direction == DIRECTION_RIGHT
			if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFTRUCK
				|| truck_y <= hm_y - HEIGHTOFMAN || truck_y >= hm_y + HEIGHTOFTRUCK)
			{
				return 0;
			}
			else
			{
				for (int i = 0, j; i < WIDTHOFMAN; i++)
				{
					for (j = 0; j < 14; j++)
					{
						if (hm_x + INHuman_PosX[i] == m_x + INTruckMoveRight_PosX[j]
							&& hm_y + INHuman_PosY[i] == truck_y + INTruckMoveRight_PosY[j])
							return 1;
					}
				}
				return 0;
			}
		}
	}
	bool FinishLane()
	{
		if (m_direction == DIRECTION_LEFT)
		{
			if (m_x <= BEGINCONSOLEWIDTHPIXELGAME - 1 - WIDTHOFTRUCK) return 1;
			return 0;
		}
		else
		{
			if (m_x >= WIDTHPIXELNUMBER + 1) return 1;
			return 0;
		}
	}
	void In(int truck_y) // y chính xác là vị trí xe
	{
		if (m_x >= BEGINCONSOLEWIDTHPIXELGAME && m_x <= WIDTHPIXELNUMBER - 1 - 7)
		{
			if (m_direction == DIRECTION_LEFT)
			{
				ToMau(m_x, truck_y, (char *)"        ", TRUCKCOLOR);
				ToMau(m_x + 2, truck_y - 1, (char *)"      ", TRUCKCOLOR);
			}
			else
			{
				ToMau(m_x, truck_y, (char *)"        ", TRUCKCOLOR);
				ToMau(m_x, truck_y - 1, (char *)"      ", TRUCKCOLOR);
			}
		}
		else
		{
			if (m_direction == DIRECTION_LEFT)
				for (int i = 0; i < 14; i++)
					ToMau(m_x + INTruckMoveLeft_PosX[i], truck_y + INTruckMoveLeft_PosY[i], ' ', TRUCKCOLOR);
			else
				for (int i = 0; i < 14; i++)
					ToMau(m_x + INTruckMoveRight_PosX[i], truck_y + INTruckMoveRight_PosY[i], ' ', TRUCKCOLOR);
		}
	}
	void InSoftlyLeft(int truck_y) // y chính xác là vị trí xe
	{
		ToMau(m_x + 0, truck_y, ' ', TRUCKCOLOR);
		ToMau(m_x + 2, truck_y - 1, ' ', TRUCKCOLOR);
		if(m_x % 2 == 0) ToMau(m_x + 8, truck_y - 1, '_', VACHROADCOLOR);
		else ToMau(m_x + 8, truck_y - 1, ' ', VACHROADCOLOR);
		ToMau(m_x + 8, truck_y, ' ', ROADCOLOR);
	}
	void InSoftlyRight(int truck_y) // y chính xác là vị trí xe
	{
		ToMau(m_x + 5, truck_y - 1, ' ', TRUCKCOLOR);
		ToMau(m_x + 7, truck_y, ' ', TRUCKCOLOR);
		if(m_x % 2 == 1) ToMau(m_x - 1, truck_y - 1, '_', VACHROADCOLOR);
		else ToMau(m_x - 1, truck_y - 1, ' ', VACHROADCOLOR);
		ToMau(m_x - 1, truck_y, ' ', ROADCOLOR);
	}
};

