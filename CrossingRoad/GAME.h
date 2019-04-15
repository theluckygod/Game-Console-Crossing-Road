#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

#include "lib.h"
#include "TRAFFICLIGHT.h"
#include "HUMAN.h"
#include "VEHICLE.h"
#include "ANIMAL.h"
#include "LANE.h"
#include "ROAD.h"
#include "ROADSIDE.h"
using namespace std;

class Game
{
private:
	int m_score;
	bool m_runState;
	vector <Lane* > m_lane;
	Human m_hm;
	int m_CurrentDirection;

	bool m_InLaiGame;
public:
	Game();

	void InGame();
	void InGameHard();
	void InGameSoftly();

	bool isRunning();
	void resetGame(); // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu
	void exitGame(); // Thực hiện thoát Thread
	void startGame(); // Thực hiện bắt đầu vào trò chơi
	void loadGame(int & DoKho, bool & AmThanh); // Thực hiện tải lại trò chơi đã lưu
	void saveGame(int DoKho, bool AmThanh); // Thực hiện lưu lại dữ liệu trò chơi
	void pauseGame(); // Tạm dừng Thread
	void resumeGame(); //Quay lai Thread
	void HumanLeftRight(char); //Thực hiện điều khiển di chuyển của Human
	void LaneLeftRight();

	bool Impact(); // Xử lý chạm xe/thú
	bool isFinish(); // Khi kết thúc trò chơi

	void Up();
	void Down();//

	int getScore() const;

	void BangChonChuongTrinh(bool &AmThanh, int &DoKho);

	void InHumanChet();

	void LaneChuaNguoi();
};