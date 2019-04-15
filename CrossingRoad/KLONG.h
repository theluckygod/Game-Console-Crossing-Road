#pragma once
#include "ANIMAL.h"

const int INKLongMoveRight_PosX[] = { 0, 1, 2, 2, 3, 4, 5, 4 };
const int INKLongMoveRight_PosY[] = { 0, 0, 0, -1, -1, -1, -1, 0 };

const int INKLongMoveLeft_PosX[] = { 0, 1, 1, 2, 3, 3, 4, 5 };
const int INKLongMoveLeft_PosY[] = { -1, 0, -1, -1, -1, 0, 0, 0};

class KLong :	public Animal
{
	static int stepKLong;
public:
	KLong(int x, int direction) : Animal(x, direction)
	{}

	static void nhayStep(int lv)
	{
		stepKLong--;
		if (stepKLong < 0) stepKLong = (NHIPKL - lv) > 0 ? (NHIPKL - lv) : 0;
	}
	bool Left()
	{
		if (stepKLong == 0)
		{
			m_x--;
			return 1;
		}
		return 0;
	}
	bool Right()
	{
		if (stepKLong == 0)
		{
			m_x++;
			return 1;
		}
		return 0;
	}
	bool impactHuman(int kl_y, int hm_x, int hm_y)
	{
		if (m_direction == DIRECTION_LEFT)
		{
			if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFKL
				|| kl_y <= hm_y - HEIGHTOFMAN || kl_y >= hm_y + HEIGHTOFKL)
			{
				return 0;
			}
			else
			{
				for (int i = 0, j; i < WIDTHOFMAN; i++)
				{
					for (j = 0; j < 8; j++)
					{
						if (hm_x + INHuman_PosX[i] == m_x + INKLongMoveLeft_PosX[j]
							&& hm_y + INHuman_PosY[i] == kl_y + INKLongMoveLeft_PosY[j])
							return 1;
					}
				}
				return 0;
			}
		}
		else
		{
			// Direction == DIRECTION_RIGHT
			if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFKL
				|| kl_y <= hm_y - HEIGHTOFMAN || kl_y >= hm_y + HEIGHTOFKL)
			{
				return 0;
			}
			else
			{
				for (int i = 0, j; i < WIDTHOFMAN; i++)
				{
					for (j = 0; j < 8; j++)
					{
						if (hm_x + INHuman_PosX[i] == m_x + INKLongMoveRight_PosX[j]
							&& hm_y + INHuman_PosY[i] == kl_y + INKLongMoveRight_PosY[j])
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
			if (m_x <= BEGINCONSOLEWIDTHPIXELGAME - 1 - WIDTHOFKL) return 1;
			return 0;
		}
		else
		{
			if (m_x >= WIDTHPIXELNUMBER + 1) return 1;
			return 0;
		}
	}
	void In(int kl_y) // y chính xác là vị trí xe
	{
		if (m_x >= BEGINCONSOLEWIDTHPIXELGAME && m_x <= WIDTHPIXELNUMBER - 1 - 7)
		{
			if (m_direction == DIRECTION_LEFT)
			{
				ToMau(m_x + 3, kl_y, (char *)"   ", KLCOLOR);
				ToMau(m_x, kl_y - 1, (char *)"    ", KLCOLOR);
				ToMau(m_x + 1, kl_y, (char *)" ", KLCOLOR);
			}
			else
			{
				ToMau(m_x, kl_y, (char *)"   ", KLCOLOR);
				ToMau(m_x + 2, kl_y - 1, (char *)"    ", KLCOLOR);
				ToMau(m_x + 4, kl_y, (char *)" ", KLCOLOR);
			}
		}
		else
		{
			if (m_direction == DIRECTION_LEFT)
				for (int i = 0; i < 8; i++)
					ToMau(m_x + INKLongMoveLeft_PosX[i], kl_y + INKLongMoveLeft_PosY[i], ' ', KLCOLOR);
			else
				for (int i = 0; i < 8; i++)
					ToMau(m_x + INKLongMoveRight_PosX[i], kl_y + INKLongMoveRight_PosY[i], ' ', KLCOLOR);
		}
	}
	void InSoftlyRight(int kl_y)
	{
		ToMau(m_x + 5, kl_y - 1, ' ', KLCOLOR);
		ToMau(m_x + 4, kl_y, ' ', KLCOLOR);
		ToMau(m_x + 3, kl_y, ' ', ROADSIDECOLOR);
		ToMau(m_x + 2, kl_y, ' ', KLCOLOR);
		if(m_x % 2 == 1) ToMau(m_x + 1, kl_y - 1, '_', VACHROADSIDECOLOR);
		else ToMau(m_x + 1, kl_y - 1, ' ', VACHROADSIDECOLOR);
		ToMau(m_x + -1, kl_y, ' ', ROADSIDECOLOR);
	}
	void InSoftlyLeft(int kl_y)
	{
		ToMau(m_x + 0, kl_y - 1, ' ', KLCOLOR);
		ToMau(m_x + 1, kl_y, ' ', KLCOLOR);
		ToMau(m_x + 2, kl_y, ' ', ROADSIDECOLOR);
		ToMau(m_x + 3, kl_y, ' ', KLCOLOR);
		if (m_x % 2 == 0) ToMau(m_x + 4, kl_y - 1, '_', VACHROADSIDECOLOR);
		else ToMau(m_x + 4, kl_y - 1, ' ', VACHROADSIDECOLOR);
		ToMau(m_x + 6, kl_y, ' ', ROADSIDECOLOR);
	}
};

