#pragma once
#include <iostream>
#include <vector>

#include "HUMAN.h"
#include "VEHICLE.h"
#include "ANIMAL.h"
#include "TRAFFICLIGHT.h"
#include "lib.h"
#include "SetupGame.h"
using namespace std;

class Lane
{
protected:
	int m_direction;
	int m_y;

	int m_diemCong;

	bool m_inLai;
public:
	Lane(int y, int direction)
	{
		m_y = y;
		m_direction = direction;

		m_diemCong = DIEMVUOTLANE;
		m_inLai = true;
	}
	int pos() const { return m_y; }

	virtual ~Lane() {}
	virtual bool isImpact(const Human& hm) = 0;
	virtual void In() = 0;

	bool hoanThanhMucGame()
	{
		return (m_y >= HEIGHTFULLPIXELNUMBER + 2 * WIDTHOFLANE);
	}
	int getDiem() 
	{
		int temp = m_diemCong;
		m_diemCong = 0;
		return temp;
	}
	void Down() // Lane di xuong
	{
		m_inLai = true;
		m_y++;
	}
	void Up() // Lane di len
	{
		m_inLai = true;
		m_y--;
	}

	void MoveLeftRight()
	{
		if (m_direction == DIRECTION_LEFT) Left();
		else Right();
	}
	virtual void Left() = 0; // Lane qua trai
	virtual void Right() = 0; // Lane qua phai

	bool ChuaNguoi(int hm_x, int hm_y)
	{
		if (hm_y <= m_y && hm_y >= m_y - WIDTHOFLANE - CACHLANE)
		{
			m_inLai = true;
			return true;
		}
		return false;
	}
	virtual void InSoftly() = 0;
};
