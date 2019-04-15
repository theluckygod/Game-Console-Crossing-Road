#pragma once
// chỉ số của Game
#define MAXSCORE 1000

// chỉ số cài đặt
#define STATE_ALIVE 1
#define STATE_DEAD 0
#define DIRECTION_LEFT -1
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 1
#define DIRECTION_UP -1

// Thông số nhịp chương trình
#define COOLDOWNRUN 150
#define COOLDOWNWAIT 100
#define NHIPXE 13
#define NHIPCAR NHIPXE
#define NHIPTRUCK NHIPXE + 3
#define NHIPTHU 20
#define NHIPDOI NHIPTHU
#define NHIPKL NHIPTHU + 5
#define NHIPWIN 5
#define MAXLEVEL 100 //
#define MUCTANGLV 8

#define FILESAVEGAME (char *)"save.txt"

#define DIEMVUOTLANE 1

// Độ khó của game
#define DOKHOEASY 100
#define DOKHONOMAL 50
#define DOKHOHARD 20

// Thông số tốc độ
#define SPEEDCAR 2
#define SPEEDSTRUCK 0
#define SPEEDDOI 5
#define SPEEDKL 0