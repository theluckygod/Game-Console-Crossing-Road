#pragma once
#include "GAME.h"

class Vehicle
{
protected:
	int m_x;
	int m_direction;
public:
	Vehicle(int x, int direction)
	{
		m_x = x;
		m_direction = direction;
	}
	virtual bool Left() = 0;
	virtual bool Right() = 0;
	virtual bool FinishLane() = 0;
	virtual bool impactHuman(int vhc_y, int hm_x, int hm_y) = 0;
	virtual void In(int vhc_y) = 0;
	virtual void InSoftlyLeft(int vhc_y) = 0;
	virtual void InSoftlyRight(int vhc_y) = 0;
	int pos()
	{
		return m_x;
	}
};