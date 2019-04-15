#pragma once
#include "LANE.h"
#include "CAR.h"
#include "TRUCK.h"

class Road : public Lane
{
private:
	bool m_hastfl;
	TrafficLight m_tfl;
	bool m_running;
	vector <Vehicle *> m_vhc;
	int m_typeVehicle;
public:
	Road(int y, int direction) : Lane(y, direction)
	{
		m_hastfl = Random::Boolean();
		m_running = true;
		m_typeVehicle = Random::SoDuong(2);
		for (int i = 0, xtemp = 0; i < NUMBEROFVHC; i++)
		{
			if (m_typeVehicle == CAR)
				m_vhc.push_back(new Car(xtemp + i * WIDTHOFCAR + i * WIDTHCACHVHC, direction));
			else 
				m_vhc.push_back(new Truck(xtemp + i * WIDTHOFTRUCK + i * WIDTHCACHVHC, direction));
		}
	}
	virtual ~Road() 
	{
		vector<Vehicle*>::iterator it = m_vhc.begin();
		for (; it != m_vhc.end(); it++)
		{
			delete *it;
		}
		m_vhc.clear();
	}

	bool isImpact(const Human& hm)
	{
		int hm_x = hm.getX(), hm_y = hm.getY();
		vector<Vehicle*>::iterator it;
		for (it = m_vhc.begin(); it != m_vhc.end(); it++)
			if ((*it)->impactHuman(m_y - 1, hm_x, hm_y)) return 1;
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
					ToMau(0, m_y - i, STRINGLANE, ROADCOLOR);
				ToMau(0, m_y - i, STRINGCHANLANE, VACHROADCOLOR);
				for (i++; i < WIDTHOFLANE - 1; i++)
					ToMau(0, m_y - i, STRINGLANE, ROADCOLOR);
				ToMau(0, m_y - i, STRINGLANE, CACHLANECOLOR);

				if (m_hastfl)
				{
					if (m_direction == DIRECTION_LEFT) m_tfl.inTrafficLight(BEGINCONSOLEWIDTHPIXELGAME, m_y - WIDTHOFLANE + HEIGHTOFLIGHT);
					else m_tfl.inTrafficLight(WIDTHPIXELNUMBER - 2, m_y - WIDTHOFLANE + HEIGHTOFLIGHT);
				}
				for (i = 0; i < NUMBEROFVHC; i++)
					m_vhc[i]->In(m_y - 1);
			}
		}
	}
	void InSoftly()
	{
		int i;
		if (m_direction == DIRECTION_LEFT)
		{
			if(m_hastfl == true) m_tfl.inTrafficLight(BEGINCONSOLEWIDTHPIXELGAME, m_y - WIDTHOFLANE + HEIGHTOFLIGHT);
			for (i = 0; i < NUMBEROFVHC; i++)
				m_vhc[i]->InSoftlyLeft(m_y - 1);
		}
		else
		{
			if (m_hastfl == true) m_tfl.inTrafficLight(WIDTHPIXELNUMBER - 2, m_y - WIDTHOFLANE + HEIGHTOFLIGHT);
			for (i = 0; i < NUMBEROFVHC; i++)
				m_vhc[i]->InSoftlyRight(m_y - 1);
		}
	}
	void Left()
	{
		int xetInLai = 0;

		if (m_hastfl)
		{
			xetInLai += m_tfl.updateLight(m_running);
		}

		if (m_running)
		{
			vector<Vehicle*>::iterator it;
			for (it = m_vhc.begin(); it != m_vhc.end(); it++)
				xetInLai += (*it)->Left();

			it = m_vhc.begin();
			if ((*it)->FinishLane())
			{
				Vehicle* temp = *it;
				for (it; it != m_vhc.end() - 1; it++)
					(*it) = *(it + 1);
				
				if (m_typeVehicle == CAR)
					*it = new Car((*(it - 1))->pos() + WIDTHOFCAR + WIDTHCACHVHC, m_direction);
				else
					*it = new Truck((*(it - 1))->pos() + WIDTHOFTRUCK + WIDTHCACHVHC, m_direction);

				delete temp;
			}
		}
		
		if (xetInLai > 0) m_inLai = true;
	}

	void Right()
	{
		int xetInLai = 0;
		if (m_hastfl)
		{
			xetInLai += m_tfl.updateLight(m_running);
		}

		if (m_running)
		{
			vector<Vehicle*>::iterator it;
			for (it = m_vhc.begin(); it != m_vhc.end(); it++)
				xetInLai += (*it)->Right();

			it = m_vhc.end() - 1;
			if ((*it)->FinishLane())
			{
				Vehicle* temp = *it;
				for (; it != m_vhc.begin(); it--)
					*it = *(it - 1);

				if (m_typeVehicle == CAR)
					*it = new Car((*(it + 1))->pos() - WIDTHOFCAR - WIDTHCACHVHC, m_direction);
				else
					*it = new Truck((*(it + 1))->pos() - WIDTHOFTRUCK - WIDTHCACHVHC, m_direction);

				delete temp;
			}
		}
		if (xetInLai > 0) m_inLai = true;
	}

	void Update()
	{
		if (m_hastfl)
			m_tfl.updateLight(m_running);
	}
};