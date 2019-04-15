#include "lib.h"

// Hàm cài đặt console
void resizeConsole(int width, int height) // Thay đổi kích thước console
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void FixConsoleWindow() // Ngăn phóng to, thu nhỏ màn hình
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void textcolor(int color) // Hàm tô màu
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, color);
}
void GotoXY(int x, int y)  // Di chuyển con trỏ console
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Nocursortype() // Ẩn con trỏ
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

// Hàm tô màu
void ToMau(int x, int y, char ch, int color) // Vẽ kí tự ch với màu color lên vị trí (x, y)
{
	if (x >= 0 && x < WIDTHPIXELNUMBER && y >= 0 && y < HEIGHTPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		cout << ch;
		GotoXY(0, 0);
	}
}
void ToMau(int x, int y, char* str, int color) // Vẽ chuỗi str với màu color lên vị trí (x, y)
{
	if (x >= 0 && x < WIDTHPIXELNUMBER && y >= 0 && y < HEIGHTPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		cout << str;
		GotoXY(0, 0);
	}
}
void ToMauToanBo(int x, int y, char* ch, int color) // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
{
	if (x >= 0 && x < WIDTHFULLPIXELNUMBER && y >= 0 && y < HEIGHTFULLPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		cout << ch;
		GotoXY(0, 0);
	}
}
void ToMauToanBo(int x, int y, char ch, int color) // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
{
	if (x >= 0 && x < WIDTHFULLPIXELNUMBER && y >= 0 && y < HEIGHTFULLPIXELNUMBER)
	{
		GotoXY(x, y);
		textcolor(color);
		cout << ch;
		GotoXY(0, 0);
	}
}
void ToMauThongBaoYOUWIN(int color)
{
	textcolor(color);
	GotoXY(WIDTHFULLPIXELNUMBER / 2 - strlen("-----<YOU WIN>-----") / 2, HEIGHTFULLPIXELNUMBER / 2);
	cout << "-----<YOU WIN>-----";
	GotoXY(0, 0);
}
void ToMauThongBao(int y, char* str) // Vẽ chuỗi str với màu color lên vị trí (x, y) bên khung thông báo
{
	textcolor(CHUCOLOR);
	GotoXY(WIDTHPIXELNUMBER + (WIDTHFULLPIXELNUMBER - WIDTHPIXELNUMBER) / 2
		- strlen(str) / 2, y);
	cout << str;
	GotoXY(0, 0);
}
void ToMauThongBaoDangChoi() // Thông báo playing
{
	ToMauThongBao(5, (char*)"State: Playing");
}
void ToMauThongBaoTamDung() // Thông báo pause
{
	ToMauThongBao(5, (char*)"State: Pause..");
}
void ToMauThongBaoHienThiDiem(int score) // in điểm
{
	textcolor(CHUCOLOR);
	GotoXY(WIDTHPIXELNUMBER + (WIDTHFULLPIXELNUMBER - WIDTHPIXELNUMBER) / 2
		- strlen("Score: ") / 2, 8);
	cout << "Score: " << score;
	GotoXY(0, 0);
}
void ToNenBatDau(int score, int DoKho, bool AmThanh)
{
	textcolor(NENCOLOR);
	std::system("cls");
	// Vẽ khung
	textcolor(KHUNGCOLOR);
	for (int i = 0; i < HEIGHTPIXELNUMBER; i++)
	{
		GotoXY(WIDTHPIXELNUMBER, i);
		cout << ' ';
	}
	ToMauThongBao(1, (char*)"Chao mung den voi");
	ToMauThongBao(2, (char*)"Game Crossing Road");
	ToMauThongBaoDangChoi();
	ToMauThongBaoHienThiDiem(score);

	if(DoKho == DOKHOEASY)
		ToMauThongBao(10, (char*)"Do kho: Easy ");
	else if (DoKho == DOKHONOMAL)
		ToMauThongBao(10, (char*)"Do kho: Nomal");
	else ToMauThongBao(10, (char*)"Do kho: Hard ");

	if(AmThanh)
		ToMauThongBao(11, (char*)"Am thanh: Bat");
	else ToMauThongBao(11, (char*)"Am thanh: Tat");
}
void ToMauThongBaoWin()
{
	int i = 0, j = -1, xchan = 0, ychan = 0;
	while (1)
	{
		for (i = xchan, j++; i < WIDTHFULLPIXELNUMBER - xchan; i += 2)
		{
			ToMauToanBo(i, j, (char *)"  ", WINCOLOR);
			Sleep(NHIPWIN);
		}
		for (i -= 2, j++; j < HEIGHTFULLPIXELNUMBER - ychan; j++)
		{
			ToMauToanBo(i, j, (char *)"  ", WINCOLOR);
			Sleep(NHIPWIN);
		}
		for (j--; i >= xchan; i -= 2)
		{
			ToMauToanBo(i, j, (char *)"  ", WINCOLOR);
			Sleep(NHIPWIN);
		}
		ychan++;
		for (i += 2, j--; j >= ychan; j--)
		{
			ToMauToanBo(i, j, (char *)"  ", WINCOLOR);
			Sleep(NHIPWIN);
		}
		xchan += 2;
		if (xchan >= WIDTHFULLPIXELNUMBER / 2) break;
	}
	ToMauThongBaoYOUWIN(CHUWINCOLOR);
}

void ToMauExitGame(bool AmThanh)
{
	/*textcolor(0);
	system("cls");*/
	ChuyenCanh(0);
	ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - strlen("Tam biet") / 2, HEIGHTFULLPIXELNUMBER / 2 - 1, (char *)"Tam biet", 10);
	if (AmThanh) PlaySound("3sExit.wav", NULL, SND_FILENAME);
	else Sleep(3000);
}

void MauMe()
{
	int mau = 0, n = 0, running = 1;
	char temp;
	int xPOS[] = { 0, WIDTHFULLPIXELNUMBER / 2, WIDTHFULLPIXELNUMBER / 2 , 0 };
	int yPOS[] = { 0, 0, HEIGHTFULLPIXELNUMBER / 2, HEIGHTFULLPIXELNUMBER / 2 };
	
	if (_kbhit())
	{
		temp = _getch();
		while (_kbhit())
		{
			temp = _getch();
		}
	}
	while (running)
	{
		textcolor(mau);

		std::system("cls");

		ToMauThongBaoYOUWIN(mau);
		mau += 16;
		if (mau >= 255) mau = 0;

		if (_kbhit())
		{
			running = 0;
			break;
		}
	}
}




string NhapDuongDan()
{
	string nhap;
	char doc;
	textcolor(CHUCOLOR);
	const int startx = WIDTHPIXELNUMBER + 2, starty = 14; // = startx + 2, starty + 2   trong HienThiSearch
	int currentx = startx;

	const int GioiHanX = WIDTHFULLPIXELNUMBER - 6; //

	GotoXY(currentx, starty);
	while (1)
	{
		if (_kbhit())
		{
			doc = 0; // Huỷ phím lưu

			doc = _getch();
			if (doc == ':' || doc == '/' || doc == '-' || doc == '_' || doc == '.' || doc == ' ' || (doc >= 'a' && doc <= 'z') || (doc >= 'A' && doc <= 'Z') || (doc >= '0' && doc <= '9'))
			{
				currentx++;
				nhap.push_back(doc);
				// in ra màn hình
				if (currentx > GioiHanX + 6) GotoXY(GioiHanX + 5, starty);
				std::cout << doc;

				if (currentx >= GioiHanX + 6 + 1)
				{
					ToMauToanBo(GioiHanX + 2, starty, (char *)"...", CHUCOLOR);
					GotoXY(GioiHanX + 5, starty);
				}
			}
			if (doc == 8) // Backspace
			{
				if (nhap.length() > 0)
				{
					doc = nhap[nhap.length() - 1];
					nhap.pop_back();

					if (currentx >= GioiHanX + 3)
					{
						currentx--;
						if (currentx > GioiHanX + 6)
						{
							ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], CHUCOLOR);
							GotoXY(GioiHanX + 5, starty);
						}
						else
						{
							if (currentx == GioiHanX + 6)
							{
								ToMauToanBo(GioiHanX + 2, starty, nhap[nhap.length() - 4], CHUCOLOR);
								ToMauToanBo(GioiHanX + 3, starty, nhap[nhap.length() - 3], CHUCOLOR);
								ToMauToanBo(GioiHanX + 4, starty, nhap[nhap.length() - 2], CHUCOLOR);
								ToMauToanBo(GioiHanX + 5, starty, nhap[nhap.length() - 1], CHUCOLOR);
								GotoXY(GioiHanX + 5, starty);
							}
							else
							{
								ToMauToanBo(currentx, starty, ' ', CHUCOLOR);
								GotoXY(currentx, starty);
							}
						}
					}
					else // Trường hợp bình thường
					{
						currentx--;
						ToMauToanBo(currentx, starty, (char *) " ", CHUCOLOR);
						GotoXY(currentx, starty);
					}

				}
			}
			if (doc == 13 && nhap.length() > 0) // Enter
				break;
		}
	}
	return nhap;
}

void ChuyenCanh(int CHUYENCANHCOLOR)
{
	int xchan = 0, ychan = 0, i = 0, j = -1 + ychan;
	int NHIPCHUYEN = 0;
	while (1)
	{
		for (i = xchan, j++; i < WIDTHFULLPIXELNUMBER - xchan; i += 2)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		for (i -= 2, j++; j < HEIGHTFULLPIXELNUMBER - ychan; j++)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		for (j--; i >= xchan; i -= 2)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		ychan++;
		for (i += 2, j--; j >= ychan; j--)
		{
			ToMauToanBo(i, j, (char *)"  ", CHUYENCANHCOLOR);
			Sleep(NHIPCHUYEN);
		}
		xchan += 2;
		if (xchan >= WIDTHFULLPIXELNUMBER / 2) break;
	}
}

void Loading()
{
	textcolor(0);
	std::system("cls");
	int start_x = WIDTHFULLPIXELNUMBER / 2 - 25, start_y = HEIGHTFULLPIXELNUMBER / 2 - 2;
	int color = 14;
	ToMauToanBo(WIDTHFULLPIXELNUMBER / 2 - 3, start_y - 1, (char *)"Loading...", 10);
	for (int i = 0; i < 50; i++)
	{
		ToMauToanBo(start_x + i, start_y, 178, color);
		ToMauToanBo(start_x + i, start_y + 1, 178, color);
		Sleep(10);
	}
}

void playWAV(char * fileWAV)
{
	PlaySound(TEXT(fileWAV), NULL, SND_FILENAME | SND_ASYNC);
}


void stopWAV(thread& playing)
{
	PlaySound(NULL, 0, 0);
	playing.join();
}