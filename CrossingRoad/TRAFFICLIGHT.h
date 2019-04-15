#pragma once
#include "GAME.h"
#include "lib.h"
#include <iostream>
enum LightState{X, V, D };

class TrafficLight
{
private:
	LightState m_state;
	int m_cooldown;
public:
	TrafficLight()
	{
		m_cooldown = Random::SoDuong(COOLDOWNRUN);
		m_state = X;
	}

	bool updateLight(bool& running)  // running = 1 if m_state = X, co in lai
	{
		if (--m_cooldown == 0)
		{
			if (m_state == X)
			{
				m_state = D;
				m_cooldown = COOLDOWNWAIT;
				running = false;
			}
			else
			{
				// chuyển đèn xanh
				m_state = X;
				m_cooldown = COOLDOWNRUN;
				running = true;
			}
			return 1;
		}
		return 0;
	}

	void inTrafficLight(int x, int y)
	{
		if(m_state == X) ToMau(x, y, (char *) "  ", DENXANHTRAFFICLIGHTCOLOR);
		else ToMau(x, y, (char *) "  ", DENDOTRAFFICLIGHTCOLOR);
	}
};

