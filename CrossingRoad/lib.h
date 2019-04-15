#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <fstream>
#include <string>
#include "Random.h"
#include "SetupGame.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

// Thông số console
#define CONSOLEFULLWIDTH 689
#define CONSOLEFULLHEIGHT 391
#define WIDTHFULLPIXELNUMBER 82
#define HEIGHTFULLPIXELNUMBER 22
#define CONSOLEWIDTH 393
#define CONSOLEHEIGHT 391
#define WIDTHPIXELNUMBER 45
#define HEIGHTPIXELNUMBER 22
#define BEGINCONSOLEWIDTHPIXELGAME 0
#define BEGINCONSOLEHEIGHTPIXELGAME 0

// Thông số hiển thị
//#define NUMBEROFLANE 4
#define WIDTHOFLANE HEIGHTPIXELNUMBER/4
#define CACHLANE 0 // 1
#define HEIGHTOFLIGHT 2

#define STRINGCHANLANE (char *)"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"
#define STRINGLANE (char *)"                                             "
#define LENGTHCAR 8
#define NUMBEROFCAR 3
#define YSTARTPOS 3 // 2
#define YLANESTART HEIGHTPIXELNUMBER - YSTARTPOS - 1;
#define NUMBEROFLANE 7
#define WIDTHCACHVHC 6
#define WIDTHCACHANM 5
#define WIDTHOFCAR 8
#define WIDTHOFTRUCK 8
#define WIDTHOFDOI 6
#define WIDTHOFKL 6
#define HEIGHTOFCAR 2
#define HEIGHTOFTRUCK 2
#define HEIGHTOFDOI 2
#define HEIGHTOFKL 2
#define NUMBEROFVHC 5
#define NUMBEROFANM 8

#define WIDTHOFMAN 2
#define HEIGHTOFMAN 1

// Thông số nhịp chương trình
//  Định nghĩa trong SetupGame.h

// Thông số màu
#define MANCOLOR 187
#define CARCOLOR 0
#define TRUCKCOLOR 0
#define DOICOLOR 0
#define KLCOLOR 0
#define NENCOLOR 255
#define CHUCOLOR 249
#define KHUNGCOLOR 0 
#define WINCOLOR 238
#define DIECOLOR 255

#define CACHLANECOLOR 119
#define LANECOLOR 200
#define VACHLANECOLOR 140
#define ROADCOLOR 136
#define VACHROADCOLOR 143
#define ROADSIDECOLOR 170
#define VACHROADSIDECOLOR 162


#define CHUWINCOLOR 234
#define CHANLANECOLOR 240


#define DENDOTRAFFICLIGHTCOLOR 204
#define DENXANHTRAFFICLIGHTCOLOR 170
#define DENVANGTRAFFICLIGHTCOLOR 238

// Type vehicle, animal
#define CAR 0
#define TRUCK 1
#define DOI 0
#define KL 1

// speed
#define SPEEDVEHICLE 2
#define SPEEDANIMAL 1
#define SPEEDHUMAN 2

// Các biến toàn cục điều khiển chương trình
//bool IS_RUNNING = true; // Sử dụng cho hàm MauMe()
//bool ChayLapChuongTrinh = true; // Sử dụng cho vòng lặp chương trình
//bool StepChay; // Sử dụng cho các step trong 1 game
//
//char m = 0, temp = 1;
//int yCurrentPosLane = 0;
//int chayXeCar = 0, chayXeTruck = 0, chayThuDoi = 0, chayThuKL = 0;
//int xposman = WIDTHPIXELNUMBER / 2;
//int yposman = HEIGHTPIXELNUMBER - YSTARTPOS;
//int score;
//int stepXeCar = NHIPXE, stepXeTruck = NHIPXE; // Tốc độ chạy của xe
//int stepThuDoi = NHIPTHU, stepThuKL = NHIPTHU; // Tốc độ chạy của thú
//int color;




// Hàm cài đặt console
void resizeConsole(int width, int height); // Thay đổi kích thước console
void FixConsoleWindow();// Ngăn phóng to, thu nhỏ màn hình
void textcolor(int color); // Hàm tô màu
void GotoXY(int x, int y);  // Di chuyển con trỏ console
void Nocursortype(); // Ẩn con trỏ

// Hàm tô màu
void ToMau(int x, int y, char ch, int color); // Vẽ kí tự ch với màu color lên vị trí (x, y)
void ToMau(int x, int y, char* str, int color); // Vẽ chuỗi str với màu color lên vị trí (x, y)
void ToMauToanBo(int x, int y, char* ch, int color); // Vẽ chuỗi str với màu color lên vị trí (x, y) cho toàn bộ vị trí
void ToMauToanBo(int x, int y, char ch, int color);
void ToMauThongBaoYOUWIN(int color);
void ToMauThongBao(int y, char* str); // Vẽ chuỗi str với màu color lên vị trí (x, y) bên khung thông báo
void ToMauThongBaoDangChoi(); // Thông báo playing
void ToMauThongBaoTamDung(); // Thông báo pause
void ToMauThongBaoHienThiDiem(int score); // in điểm
void ToNenBatDau(int score, int DoKho, bool AmThanh);
void ToMauThongBaoWin();
void ToMauExitGame(bool AmThanh);


void MauMe();
string NhapDuongDan();

void ChuyenCanh(int CHUYENCANHCOLOR);
void Loading();

void playWAV(char * fileWAV);
void stopWAV(thread& playing);