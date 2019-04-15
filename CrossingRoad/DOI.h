#pragma once
#include "ANIMAL.h"

const int INDoi_PosX[] = { 0, 1, 2, 3, 4, 5 };
const int INDoi_PosY[] = { -1, -1, 0, 0, -1, -1 };

class Doi :	public Animal
{
	static int stepDoi;
public:
	Doi(int x, int direction) : Animal(x, direction)
	{}

	static void nhayStep(int lv)
	{
		stepDoi--;
		if (stepDoi < 0) stepDoi = (NHIPDOI - lv) > 0? (NHIPDOI - lv) : 0;
	}
	bool Left()
	{
		if (stepDoi == 0)
		{
			m_x--;
			return 1;
		}
		return 0;
	}
	bool Right()
	{
		if (stepDoi == 0)
		{
			m_x++;
			return 1;
		}
		return 0;
	}
	bool impactHuman(int doi_y, int hm_x, int hm_y)
	{
		if (m_x >= hm_x + WIDTHOFMAN || m_x <= hm_x - WIDTHOFDOI
			|| doi_y <= hm_y - HEIGHTOFMAN || doi_y >= hm_y + HEIGHTOFDOI)
		{
			return 0;
		}
		else
		{
			for (int i = 0, j; i < WIDTHOFMAN; i++)
			{
				for (j = 0; j < 6; j++)
				{
					if (hm_x + INHuman_PosX[i] == m_x + INDoi_PosX[j]
						&& hm_y + INHuman_PosY[i] == doi_y + INDoi_PosY[j])
						return 1;
				}
			}
			return 0;
		}
	}
	bool FinishLane()
	{
		if (m_direction == DIRECTION_LEFT)
		{
			if (m_x <= BEGINCONSOLEWIDTHPIXELGAME - 1 - WIDTHOFDOI) return 1;
			return 0;
		}
		else
		{
			if (m_x >= WIDTHPIXELNUMBER + 1) return 1;
			return 0;
		}
	}
	void In(int doi_y) // y chính xác là vị trí xe
	{
		if (m_x >= BEGINCONSOLEWIDTHPIXELGAME && m_x <= WIDTHPIXELNUMBER - 1 - 7)
		{
			ToMau(m_x, doi_y - 1, (char *)"  ", DOICOLOR);
			ToMau(m_x + 2, doi_y, (char *)"  ", DOICOLOR);
			ToMau(m_x + 4, doi_y - 1, (char *)"  ", DOICOLOR);
		}
		else
		{
			for (int i = 0; i < 6; i++)
				ToMau(m_x + INDoi_PosX[i], doi_y + INDoi_PosY[i], ' ', DOICOLOR);
		}
	}
	void InSoftlyRight(int doi_y)
	{
		ToMau(m_x + 5, doi_y - 1, ' ', DOICOLOR);
		ToMau(m_x + 3, doi_y, ' ', DOICOLOR);
		if (m_x % 2 == 1)
		{
			ToMau(m_x + 3, doi_y - 1, '_', VACHROADSIDECOLOR);
			ToMau(m_x - 1, doi_y - 1, '_', VACHROADSIDECOLOR);
		}
		else
		{
			ToMau(m_x + 3, doi_y - 1, ' ', VACHROADSIDECOLOR);
			ToMau(m_x - 1, doi_y - 1, ' ', VACHROADSIDECOLOR);
		}
		ToMau(m_x + 1, doi_y - 1, ' ', DOICOLOR);
		ToMau(m_x + 1, doi_y, ' ', ROADSIDECOLOR);

	}
	void InSoftlyLeft(int doi_y)
	{
		ToMau(m_x + 0, doi_y - 1, ' ', DOICOLOR);
		ToMau(m_x + 2, doi_y, ' ', DOICOLOR);
		if(m_x % 2 == 0)
		{
			ToMau(m_x + 2, doi_y - 1, '_', VACHROADSIDECOLOR);
			ToMau(m_x + 6, doi_y - 1, '_', VACHROADSIDECOLOR);
		}
		else 
		{
			ToMau(m_x + 2, doi_y - 1, ' ', VACHROADSIDECOLOR);
			ToMau(m_x + 6, doi_y - 1, ' ', VACHROADSIDECOLOR);
		}
		ToMau(m_x + 4, doi_y - 1, ' ', DOICOLOR);
		ToMau(m_x + 4, doi_y, ' ', ROADSIDECOLOR);
	}
};

