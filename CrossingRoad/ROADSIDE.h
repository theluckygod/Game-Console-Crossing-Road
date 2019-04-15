#pragma once
#include "LANE.h"
#include "lib.h"
#include "DOI.h"
#include "KLONG.h"

class RoadSide : public Lane
{
private:
	vector <Animal *> m_anm;
	int m_typeAnimal;
public:
	RoadSide(int y, int direction) : Lane(y, direction)
	{
		m_typeAnimal = Random::SoDuong(2);
		for (int i = 0, xtemp = 0; i < NUMBEROFANM; i++)
		{
			if (m_typeAnimal == DOI)
				m_anm.push_back(new Doi(xtemp + i * WIDTHOFDOI + i * WIDTHCACHANM, direction));
			else
				m_anm.push_back(new KLong(xtemp + i * WIDTHOFKL + i * WIDTHCACHANM, direction));
		}
	}
	virtual ~RoadSide() 
	{
		vector<Animal*>::iterator it = m_anm.begin();
		for (; it != m_anm.end(); it++)
		{
			delete *it;
		}
		m_anm.clear();
	}

	bool isImpact(const Human& hm)
	{
		vector<Animal*>::iterator it;
		for (it = m_anm.begin(); it != m_anm.end(); it++)
			if ((*it)->impactHuman(m_y - 1, hm.getX(), hm.getY())) return 1;
		return 0;
	}

	void In()
	{
		if (m_y >= 0 && m_y < HEIGHTFULLPIXELNUMBER + WIDTHOFLANE + CACHLANE)
		{
			if (m_inLai == true)
			{
				m_inLai = false;

				int i;
				for (i = 0; i < WIDTHOFLANE / 2; i++)
					ToMau(0, m_y - i, STRINGLANE, ROADSIDECOLOR);
				ToMau(0, m_y - i, STRINGCHANLANE, VACHROADSIDECOLOR);
				for (i++; i < WIDTHOFLANE - 1; i++)
					ToMau(0, m_y - i, STRINGLANE, ROADSIDECOLOR);
				ToMau(0, m_y - i, STRINGLANE, CACHLANECOLOR);

				for (i = 0; i < NUMBEROFANM; i++)
					m_anm[i]->In(m_y - 1);
			}
		}
	}

	void InSoftly()
	{
		int i;
		if (m_direction == DIRECTION_LEFT)
			for (i = 0; i < NUMBEROFANM; i++)
				m_anm[i]->InSoftlyLeft(m_y - 1);
		else
			for (i = 0; i < NUMBEROFANM; i++)
				m_anm[i]->InSoftlyRight(m_y - 1);
	}

	void Left()
	{
		vector<Animal*>::iterator it;
		int xetInLai = 0;
		for (it = m_anm.begin(); it != m_anm.end(); it++)
			xetInLai += (*it)->Left();
		if (xetInLai > 0) m_inLai = true;

		it = m_anm.begin();
		if ((*it)->FinishLane())
		{
			Animal* temp = *it;
			for (it; it != m_anm.end() - 1; it++)
				(*it) = *(it + 1);

			if (m_typeAnimal == DOI)
				*it = new Doi((*(it - 1))->pos() + WIDTHOFDOI + WIDTHCACHANM, m_direction);
			else
				*it = new KLong((*(it - 1))->pos() + WIDTHOFKL + WIDTHCACHANM, m_direction);

			delete temp;
		}
	}

	void Right()
	{
		vector<Animal*>::iterator it;
		int xetInLai = 0;
		for (it = m_anm.begin(); it != m_anm.end(); it++)
			xetInLai += (*it)->Right();
		if (xetInLai > 0) m_inLai = true;

		it = m_anm.end() - 1;
		if ((*it)->FinishLane())
		{
			Animal* temp = *it;
			for (; it != m_anm.begin(); it--)
				*it = *(it - 1);

			if (m_typeAnimal == DOI)
				*it = new Doi((*(it + 1))->pos() - WIDTHOFDOI - WIDTHCACHANM, m_direction);
			else
				*it = new KLong((*(it + 1))->pos() - WIDTHOFKL - WIDTHCACHANM, m_direction);

			delete temp;
		}
	}
};

