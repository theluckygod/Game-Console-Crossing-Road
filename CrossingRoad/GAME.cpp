#include "GAME.h"

Game::Game()
{
	m_InLaiGame = true;
	m_score = 0;
	m_runState = 1;
	m_CurrentDirection = Random::Boolean() ? DIRECTION_LEFT : DIRECTION_RIGHT;

	int ytemp = HEIGHTPIXELNUMBER - YSTARTPOS - 1;
	for (int i = 0; i < NUMBEROFLANE; i++)
	{
		int test = ytemp - i * int(WIDTHOFLANE) - i * CACHLANE;
		if (Random::Boolean() == 0)
			m_lane.push_back(new Road(test, m_CurrentDirection));
		else  m_lane.push_back(new RoadSide(test, m_CurrentDirection));

		m_CurrentDirection *= -1;
	}
}

bool Game::isRunning()
{
	return m_runState;
}

void Game::InGame()
{
	if (m_InLaiGame == true)
	{
		m_InLaiGame = false;
		InGameHard();
	}
	else
		InGameSoftly();
}
void Game::InGameHard()
{
	int hm_x = m_hm.getX(), hm_y = m_hm.getY();

	ToMau(hm_x - 2, hm_y, (char *) "    ", NENCOLOR);
	ToMau(hm_x + 2, hm_y, (char *)" ", NENCOLOR);
	ToMau(hm_x + 3, hm_y, (char *)" ", NENCOLOR);

	for (int i = 0, size = m_lane.size(); i < size; i++)
	{
		m_lane[i]->In();
	}

	m_hm.In();
}
void Game::InGameSoftly()
{
	int hm_x = m_hm.getX(), hm_y = m_hm.getY();
	
	ToMau(hm_x - 2, hm_y, (char *) "    ", NENCOLOR);
	ToMau(hm_x + 2, hm_y, (char *)" ", NENCOLOR);
	ToMau(hm_x + 3, hm_y, (char *)" ", NENCOLOR);

	for (int i = 0, size = m_lane.size(); i < size; i++)
	{
		if(m_lane[i]->ChuaNguoi(hm_x, hm_y)) m_lane[i]->In();
		else m_lane[i]->InSoftly();
	}

	m_hm.In();
}

void Game::resetGame()
{
	m_InLaiGame = true;
	m_score = 0;
	m_runState = true;
	for (int i = 0, size = m_lane.size(); i < size; i++)
	{
		delete m_lane[i];
	}
	m_lane.clear();
	int ytemp = HEIGHTPIXELNUMBER - YSTARTPOS - 1;
	for (int i = 0; i < NUMBEROFLANE; i++)
	{
		int test = ytemp - i * int(WIDTHOFLANE) - i * CACHLANE;
		if (Random::Boolean() == 0)
			m_lane.push_back(new Road(test, m_CurrentDirection));
		else  m_lane.push_back(new RoadSide(test, m_CurrentDirection));

		m_CurrentDirection *= -1;
	}

	m_hm.reset();
}
void Game::exitGame()
{
	m_runState = 0;
	for (int i = 0, size = m_lane.size(); i < size; i++)
	{
		delete m_lane[i];
	}
	m_hm.reset();
}
void Game::startGame()
{
	m_runState = true;
}
void Game::loadGame(int &DoKho, bool &AmThanh)
{
	ToMauToanBo(WIDTHPIXELNUMBER + 2, 13, (char *)"                                   ", CHUCOLOR);
	ToMauToanBo(WIDTHPIXELNUMBER + 2, 14, (char *)"                                   ", CHUCOLOR);

	ToMauToanBo(WIDTHPIXELNUMBER + 2, 13, (char *)"Nhap ten file: ", CHUCOLOR);
	string fileName = NhapDuongDan();
	ifstream in(fileName, ios::binary);
	//ifstream in(FILESAVEGAME);
	if (!in.is_open())
	{
		m_score = 0;
		textcolor(0);
		std::system("cls");
		ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("Khong luu truoc do") / 2, HEIGHTFULLPIXELNUMBER / 2, (char *)"Khong luu truoc do", 10);

		if(AmThanh) PlaySound("2sLoadFail.wav", NULL, SND_FILENAME);
		else Sleep(2000);

		textcolor(0);
		std::system("cls");
	}
	else
	{
		in.read(reinterpret_cast<char *>(&m_score), sizeof(m_score));
		in.seekg(5);
		in.read(reinterpret_cast<char *>(&DoKho), sizeof(DoKho));

		in.close();
	}
}
void Game::saveGame(int DoKho, bool AmThanh)
{
	ToMauThongBaoTamDung();

	ToMauToanBo(WIDTHPIXELNUMBER + 2, 13, (char *)"Nhap ten file: ", CHUCOLOR);
	string fileName = NhapDuongDan();
	ofstream out(fileName, ios::binary);
	//ofstream out(FILESAVEGAME);


	out.write(reinterpret_cast<char *>(&m_score), sizeof(m_score));
	out.write("", sizeof(""));
	out.write(reinterpret_cast<char *>(&DoKho), sizeof(DoKho));

	out.close();
	ToMauThongBao(16, (char *)"Da luu!");
	ToMauThongBao(17, (char *)"Ban co muon tiep tuc(Y/N)?");

	char luachon = 0;
	while (1)
	{
		if (_kbhit())
		{
			luachon = toupper(_getch());
		}
		if (luachon == 'Y' || luachon == 'N') break;
	}
	switch (luachon)
	{
	case 'N': 
		exitGame();
		ToMauExitGame(AmThanh);
		exit(0);
		break;
	case 'Y':
		ToMauThongBao(16, (char *)"       ");
		ToMauThongBao(17, (char *)"                          ");
		ToMauToanBo(WIDTHPIXELNUMBER + 2, 13, (char *)"               ", CHUCOLOR);
		ToMauToanBo(WIDTHPIXELNUMBER + 2, 14, (char *)"                                   ", CHUCOLOR);
		ToMauThongBaoDangChoi();
	}

}
void Game::pauseGame()
{
	m_runState = false;
}
void Game::resumeGame()
{
	m_runState = true;
}
void Game::HumanLeftRight(char move)
{
	switch (move)
	{
	case 'A':
		m_hm.Left();
		break;
	case 'D':
		m_hm.Right();
		break;
	}
}
void Game::LaneLeftRight()
{
	for (int i = 0, size = m_lane.size(); i < size; i++)
		m_lane[i]->MoveLeftRight();
}



bool Game::Impact()
{
 	bool impact = m_lane[0]->isImpact(m_hm);
	if (impact == 0)
	{
		impact = m_lane[1]->isImpact(m_hm);
		if (impact == 0)
		{
			impact = m_lane[2]->isImpact(m_hm);
			if (impact == 0) impact = m_lane[3]->isImpact(m_hm);
		}
	}

	if (impact == true)
	{
		m_hm.Dead();
		m_runState = false;
	}
	return impact;
}

bool Game::isFinish()
{
	return (m_score >= MAXLEVEL);
}


void Game::Down() // Lane down
{
	m_InLaiGame = true;

	int i = 0, size = m_lane.size();
	for (; i < size; i++)
		m_lane[i]->Down();

	// Hoàn thành mức lane -> xoá lane
	if (m_lane[0]->hoanThanhMucGame())
	{
		delete m_lane[0];


		i = 0, size = m_lane.size();
		for (; i < size - 1; i++)
			m_lane[i] = m_lane[i + 1];
		
		if (Random::Boolean() == 0)
			m_lane[i] = new Road(m_lane[i - 1]->pos() - WIDTHOFLANE - CACHLANE, m_CurrentDirection);
		else  m_lane[i] = new RoadSide(m_lane[i - 1]->pos() - WIDTHOFLANE - CACHLANE, m_CurrentDirection);
		m_CurrentDirection *= -1;
	}

	if (m_hm.getY()  == m_lane[1]->pos() + 1 - WIDTHOFLANE)
		m_score += m_lane[1]->getDiem();
	else
		if(m_hm.getY() == m_lane[0]->pos() + 1 - WIDTHOFLANE)
			m_score += m_lane[0]->getDiem();

}

void Game::Up() // Lane up
{
	if (m_lane[1]->pos() == m_hm.getY() || m_lane[0]->pos() < m_hm.getY() + 3) return;

	m_InLaiGame = true;

	int i = 0, size = m_lane.size();
	for (; i < size; i++)
		m_lane[i]->Up();

	//if (m_hm.getY() <= m_lane[0]->pos() - WIDTHOFLANE) m_score++;
}

int Game::getScore() const
{
	return m_score;
}

void Game::BangChonChuongTrinh(bool &AmThanh, int &DoKho)
{
	textcolor(0);
	std::system("cls");
	int luachon;
	while (1)
	{
		luachon = 0;
		ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("1. New game") / 2, HEIGHTFULLPIXELNUMBER / 2 - 2, (char *)"1. New game", 10);
		ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("1. New game") / 2, HEIGHTFULLPIXELNUMBER / 2 - 1, (char *)"2. Load game", 10);
		ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("1. New game") / 2, HEIGHTFULLPIXELNUMBER / 2, (char *)"3. Settings", 10);
		ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("1. New game") / 2, HEIGHTFULLPIXELNUMBER / 2 + 1, (char *)"0. Exit", 10);
		if (_kbhit())
		{
			luachon = _getch();
		}
		if (luachon == '1' || luachon == '2' || luachon == '0')
		{
			if (AmThanh) PlaySound("0sPick.wav", NULL, SND_FILENAME);
			else Sleep(500);
			break;
		}
		else if (luachon == '3')
		{
			textcolor(0);
			std::system("cls");

			while (1)
			{
				luachon = 0;
				if(DoKho == DOKHOEASY)
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 8, (char *)"Hien Tai: Easy ", 10);
				else if (DoKho == DOKHONOMAL)
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 8, (char *)"Hien Tai: Nomal", 10);
				else 
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 8, (char *)"Hien Tai: Hard ", 10);
				
				if(AmThanh == true)
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 7, (char *)"          Bat am", 10);
				else
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 7, (char *)"          Tat am", 10);

				ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 2, (char *)"1. Do kho Easy", 10);
				ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 - 1, (char *)"2. Do kho Nomal", 10);
				ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2, (char *)"3. Do kho Hard", 10);
				if(AmThanh)
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 + 1, (char *)"4. Tat am", 10);
				else
					ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 + 1, (char *)"4. Bat am", 10);
				ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("2. Do kho Nomal") / 2, HEIGHTFULLPIXELNUMBER / 2 + 2, (char *)"0. Back", 10);
				if (_kbhit())
				{
					luachon = _getch();
				}
				if (luachon == '0') break;
				if (luachon == '1' || luachon == '2' || luachon == '3' || luachon == '4')
				{
					if (AmThanh) PlaySound("0sPick.wav", NULL, SND_FILENAME);
					else Sleep(500);
					if (_kbhit())
					{
						char temp = _getch();
						while (_kbhit())
						{
							temp = _getch();
						}
					}

					switch (luachon - '0')
					{
					case 1:
						DoKho = DOKHOEASY;
						break;
					case 2:
						DoKho = DOKHONOMAL;
						break;
					case 3:
						DoKho = DOKHOHARD;
						break;
					case 4:
						AmThanh = !AmThanh;
						break;
					}
				}

			}

			textcolor(0);
			std::system("cls");
		}

	}
	
	switch (luachon - '0')
	{
	case 0:
		m_runState = 0;
		break;
	case 1: 
		m_score = 0; 
		break;
	case 2:
		loadGame(DoKho, AmThanh);
		break;
	}
}

void Game::InHumanChet()
{
	m_hm.InChet();
}

void Game::LaneChuaNguoi()
{
	int hm_x = m_hm.getX(), hm_y = m_hm.getY();
	vector<Lane *>::iterator it = m_lane.begin();
	for (; it != m_lane.end(); it++)
		(*it)->ChuaNguoi(hm_x, hm_y);
}