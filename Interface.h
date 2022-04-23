#pragma once
#include "Config.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int ENTER = 13;
const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int SPACE = 32;
const int ESC = 27;
const int DEL = 83;
const int BACKGROUND_WHITE = 0x0070;
const int FOREGROUND_WHITE = 7;
const int BACKGROUND_BRIGHTWHITE = 0x00f0;
const int FOREGROUND_BRIGHTWHITE = 15;
const int BACKGROUND_LIGHTGREEN = 0x00a0;
const int FOREGROUND_LIGHTGREEN = 10;
const int BACKGROUND_CYAN = 0x0030;
const int FOREGROUND_CYAN = 3;
const int BACKGROUND_LIGHTCYAN = 0x00b0;
const int FOREGROUND_LIGHTCYAN = 11;
const int BACKGROUND_LIGHTBLUE = 0x0090;
const int FOREGROUND_LIGHTBLUE = 9;
const int BACKGROUND_GRAY = 0x0080;
const int FOREGROUND_GRAY = 8;
const int BACKGROUND_LIGHTYELLOW = 0x00e0;
const int FOREGORUND_LIGHTYELLOW = 14;
const int BACKGROUND_LIGHTRED = 0x00c0;
const int FOREGROUND_LIGHTRED = 12;	
const int BACKGROUND_LIGHTPURPLE = 0x00d0;
const int FOREGROUND_LIGHTPURPLE = 13;
const int BACKGROUND_PURPLE = 0x0050;
const int FOREGROUND_PURPLE = 5;
const int BACKGROUND_YELLOW = 0x0060;
const int FOREGROUND_YELLOW = 6;

void setColor(WORD color);
void normal();
void gotoxy(SHORT x, SHORT y);
void alignCenter(string s, int coordX, int coordY, int horizontal);
void alignCenter(double grade, int coordX, int coordY, int horizontal);
void alignCenter(string s1, double grade, string s2, int coordX, int coordY, int horizontal);
void drawRectangle(int coordX, int coordY, int horizontal, int vertical);
void drawRectangle1(int coordX, int coordY, int horizontal, int vertical, int color);
void drawRectangle2(int coordX, int coordY, int horizontal, int vertical, int color);
void addButton(string s, int coordX, int coordY, int horizontal, int vertical, int FG, int BG);
void addButton1(string s, char ch, int coordX, int coordY, int horizontal, int vertical, int FG, int BG);
void addButton2(string s, int coordX, int coordY, int horizontal, int vertical, int FG, int BG);
void clearPartOfScreen(int coordX, int coordY, int horizontal, int vertical);
void notification(string s, int coordX, int coordY, int horizontal, int vertical, int color);  
void notification1(string s, int x, int y, int horizontal, int vertical, int color);
void drawTable1(int coordX, int coordY, int horizontal, int vertical);
void table1(int coordX, int coordY, int horizontal, int vertical, string menu[4], int mode); 
void clearTable1(int coordX, int coordY, int horizontal, int vertical);
void infoBar1(int coordX, int coordY, int horizontal, ClassList b, int i);
void infoBar2(int coordX, int coordY, int horizontal, SubjectList a, int i);
void lightBar1(int coordX, int coordY, int horizontal, int color);
bool verifyingDeleteBlock(int coordX, int coordY);
void notificationBlock(string s, int coordX, int coordY, int horizontal, int color);
void drawTable2();
void table2(string s, int mode);
void clearTable2();
void drawTable2();
void table3(Subject a, Class b);
void clearTable3();
void breakLine(int x, int y, string s, int bound);
void infoBar3(int x, int y, StudentNode *p, int i);
void infoBar3(int x, int y, StudentNode *p, int index, Subject a);
void lightBar2(int x, int y, int horizontal, int color);
void lightBar3(int x, int y, int horizontal, int color);
