#include "Random.h"
#include <ctime>
#include <iostream>
using namespace std;


Random::Random()
{
	srand(time(NULL));
}

int Random::Next()
{
	int sign = (rand() % 2 == 1) ? -1 : 1;
	return rand() * sign;
}

int Random::Next(int max)
{
	if (max == 0)
	{
		cout << "Nhap max khong hop le!\n";
		return -1;
	}
	return rand() % max;
}

int Random::SoDuong()
{
	return rand() + 1;
}

int Random::SoDuong(int max)
{
	if (max == 0)
	{
		cout << "Nhap max khong hop le!\n";
		return -1;
	}
	return rand() % max;
}

bool Random::Boolean()
{
	return rand() % 2;
}