#pragma once
#include "GAME.h"

class Animal
{
protected:
	int m_x;
	int m_direction;
public:
	Animal(int x, int direction)
	{
		m_x = x;
		m_direction = direction;
	}
	virtual bool Left() = 0;
	virtual bool Right() = 0;
	virtual bool FinishLane() = 0;

	virtual bool impactHuman(int anm_y, int hm_x, int hm_y) = 0;
	virtual void In(int anm_y) = 0;
	virtual void InSoftlyLeft(int anm_y) = 0;
	virtual void InSoftlyRight(int anm_y) = 0;
	int pos()
	{
		return m_x;
	}
};