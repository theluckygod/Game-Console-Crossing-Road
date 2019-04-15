#include "GAME.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <stdio.h>
#include "lib.h"
using namespace std;

int Car::stepCar = NHIPCAR;
int Truck::stepTruck = NHIPTRUCK;
int Doi::stepDoi = NHIPDOI;
int KLong::stepKLong = NHIPKL;

int NhipDoKho = DOKHONOMAL;
int score;
bool AmThanh = true;

int main()
{
	// Không dụng vào
	resizeConsole(CONSOLEFULLWIDTH, CONSOLEHEIGHT);
	FixConsoleWindow();
	Nocursortype();
	Random();

	bool ChayLapChuongTrinh = 1;
	Game gm_gl;
	char m, temp = ' ';
	thread nhacNen;
	thread nhacWin;

	do
	{
		Loading();//
		gm_gl.BangChonChuongTrinh(AmThanh, NhipDoKho);
		if (gm_gl.isRunning())
		{
			score = gm_gl.getScore();
			ChuyenCanh(NENCOLOR);//
			ToNenBatDau(score, NhipDoKho, AmThanh);
			if (AmThanh == true)
			{
				nhacNen = thread(&playWAV, (char *) "Nhacnen.wav");
			}
		}
		else break; // Bấm chọn Exit
		while (gm_gl.isRunning())
		{
			m = ' '; // Huỷ phím bị lưu step trước
			// Bắt phím
			if (_kbhit())
			{
				m = _getch();
				// Huỷ các phím bấm quá dư
				while (_kbhit())
				{
					temp = _getch();
				}
			}

			// Điều khiển di chuyển
			switch (m)
			{
			case 'W': case 'w': 
				gm_gl.Down(); 
				score = gm_gl.getScore(); 
				break;
			case 's': case 'S': 
				gm_gl.Up();
				break;
			case 'A': case 'a':
				gm_gl.HumanLeftRight('A');
				break;
			case 'D': case 'd':
				gm_gl.HumanLeftRight('D');
				break;
			case 'L': case 'l':
				gm_gl.saveGame(NhipDoKho, AmThanh);
				break;
			case 'T': case 't':
				ToMauThongBaoTamDung();
				gm_gl.resetGame();

				gm_gl.loadGame(NhipDoKho, AmThanh);
				score = gm_gl.getScore();
				ChuyenCanh(NENCOLOR);//
				ToNenBatDau(score, NhipDoKho, AmThanh);
				ToMauThongBaoDangChoi();
				
				if (nhacNen.joinable())
				{
					stopWAV(nhacNen);
				}
				if (AmThanh == true)	nhacNen = thread(&playWAV, (char *) "Nhacnen.wav");

				break;
			}
			
	
			ToMauThongBaoHienThiDiem(score);

			gm_gl.InGame();

			// Đụng chạm
			if (gm_gl.Impact())
			{
				if (nhacNen.joinable())
				{
					stopWAV(nhacNen);
				}

				// Thể hiện thua
				gm_gl.InHumanChet();
				ToMauThongBao(14, (char *)"You lose!");
				
				if (AmThanh) PlaySound("3sambulanc.wav", NULL, SND_FILENAME);
				else Sleep(3000);
			}

			// Nhịp xe chay
			Car::nhayStep(score / MUCTANGLV);
			Truck::nhayStep(score / MUCTANGLV);
			Doi::nhayStep(score / MUCTANGLV);
			KLong::nhayStep(score / MUCTANGLV);


			gm_gl.LaneLeftRight();



			// win game
			if (gm_gl.isFinish())
			{
				if (nhacNen.joinable())
				{
					stopWAV(nhacNen);
				}

				break; // win
			}

			Sleep(NhipDoKho);
		}

		if (gm_gl.isRunning())
		{
			if (AmThanh)
				nhacWin = thread(&playWAV, (char *) "win.wav");

			// Thể hiện win
			ToMauThongBaoWin();
			
			//if (AmThanh) PlaySound("2sWin.wav", NULL, SND_FILENAME);
			//else Sleep(2000);
			



			

			// congratulate;
			MauMe();


			//// Bắt phím để kết thúc
			//if (_kbhit())
			//{
			//	temp = _getch();
			//	while (_kbhit())
			//	{
			//		temp = _getch();
			//	}
			//}
			//while (1)
			//{
			//	if (_kbhit()) break;
			//}
		}
		
		// Kết thúc 1 vòng chương trình

		// Hoi tt
		ToMauThongBao(18, (char *) "Ban muon tiep tuc(Y/N)?");

		// Bắt phím
		while (1)
		{
			if (_kbhit())
			{
				m = _getch();
				if (m == 'Y' || m == 'y' || m == 'n' || m == 'N')
				{
					if (nhacWin.joinable()) stopWAV(nhacWin);//
					break;
				}
			}
		}
		// Huỷ các phím bấm quá dư
		while (_kbhit())
		{
			temp = _getch();
		}

		switch (m)
		{
		case 'n': case 'N': ChayLapChuongTrinh = false; break;
		}


		if (ChayLapChuongTrinh == true)
		{
			gm_gl.resetGame();
		}
	} while (ChayLapChuongTrinh);
	ToMauExitGame(AmThanh);
	return 0;
}