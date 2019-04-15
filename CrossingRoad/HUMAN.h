#pragma once
#include "Vehicle.h"
#include "lib.h"
const int INHuman_PosX[] = { 0, 1 };
const int INHuman_PosY[] = { 0, 0 };

class Human
{
private:
	int m_x, m_y;
	bool m_state;
private:
	//void drawHelper(int COLOR);
public:
	Human()
	{
		m_x = WIDTHPIXELNUMBER / 2;
		m_y = HEIGHTPIXELNUMBER - YSTARTPOS;
		m_state = STATE_ALIVE;
	}

	int getX() const
	{
		return m_x;
	}
	int getY() const
	{
		return m_y;
	}
	void Left()
	{
		if (m_x > BEGINCONSOLEWIDTHPIXELGAME + 1)
		{
			m_x -= 2;
		}
		else if (m_x == BEGINCONSOLEWIDTHPIXELGAME + 1) m_x--;
	}
	void Right()
	{
		if (m_x < WIDTHPIXELNUMBER - 3) m_x += 2;
		else if (m_x == WIDTHPIXELNUMBER - 3) m_x++;
	}

	void In()
	{
		for (int i = 0; i < 2; i++)
			ToMau(m_x + i, m_y, ' ', MANCOLOR);
	}
	void reset()
	{
		m_x = WIDTHPIXELNUMBER / 2;
		m_y = HEIGHTPIXELNUMBER - YSTARTPOS;
		m_state = STATE_ALIVE;
	}
	
	void Dead()
	{
		m_state = STATE_DEAD;
	}

	bool isDead()
	{
		return m_state == STATE_DEAD;
	}

	void InChet()
	{
		ToMau(m_x, m_y - 3, (char *) "  ", DIECOLOR);
		ToMau(m_x - 2, m_y - 2, (char *) "  ", DIECOLOR);
		ToMau(m_x, m_y - 2, (char *) "  ", DIECOLOR);
		ToMau(m_x + 2, m_y - 2, (char *) "  ", DIECOLOR);
		ToMau(m_x, m_y - 1, (char *) "  ", DIECOLOR);
		ToMau(m_x, m_y, (char *) "  ", DIECOLOR);
	}
};

