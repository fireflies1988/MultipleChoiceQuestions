#include "Interface.h"
#include <iomanip>

void setColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(SHORT x, SHORT y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{x, y});
}
void normal()
{
	setColor(FOREGROUND_WHITE);
}
void alignCenter(string s, int coordX, int coordY, int horizontal)
{
	gotoxy(coordX + (horizontal - s.length()) / 2, coordY); cout << s;
}
void alignCenter(string s1, double grade, string s2, int coordX, int coordY, int horizontal)
{
	string s = s1 + string(2, ' ') + s2;
	gotoxy(coordX + (horizontal - s.length()) / 2, coordY); 	
	cout << setprecision(2) << s1 << grade << s2;
}
void alignCenter(double grade, int coordX, int coordY, int horizontal)
{
	gotoxy(coordX + (horizontal - 2) / 2, coordY);
	cout << setprecision(2) << grade;
}
void drawRectangle(int coordX, int coordY, int horizontal, int vertical)
{
	gotoxy(coordX, coordY); 
	cout << char(218) << string(horizontal - 2, char(196)) << char(191);
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX, coordY + i + 1);
		cout << char(179);
		gotoxy(coordX + horizontal - 1, coordY + i + 1);
		cout << char(179);
	}
	gotoxy(coordX, coordY + vertical - 1);
	cout << char(192) << string(horizontal - 2, char(196)) << char(217);
}
void drawRectangle1(int coordX, int coordY, int horizontal, int vertical, int color)
{
	gotoxy(coordX, coordY);
	setColor(color);
	cout << string(horizontal, ' ');
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX, coordY + i + 1);		cout << string(2, ' ');
		gotoxy(coordX + horizontal - 2, coordY + i + 1);	cout << string(2, ' ');		
	}
	gotoxy(coordX, coordY + vertical - 1);
	cout << string(horizontal, ' ');
}
void drawRectangle2(int coordX, int coordY, int horizontal, int vertical, int color)
{
	gotoxy(coordX, coordY);
	setColor(color);
	cout << string(horizontal, ' ');
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX, coordY + i + 1);		cout << ' ';
		gotoxy(coordX + horizontal - 1, coordY + i + 1);	cout << ' ';		
	}
	gotoxy(coordX, coordY + vertical - 1);
	cout << string(horizontal, ' ');
}
void addButton(string s, int coordX, int coordY, int horizontal, int vertical, int FG, int BG)
{
	setColor(BG);
	for (int i = 0; i < vertical; i++)
	{
		gotoxy(coordX, coordY + i);
		cout << string(horizontal, ' ');
	}
	setColor(FG | BG);
	alignCenter(s, coordX, coordY + vertical / 2, horizontal);
}
void addButton1(string s, char ch, int coordX, int coordY, int horizontal, int vertical, int FG, int BG) // ch la A, B, C, D danh cho phan cau hoi
{
	setColor(BG);
	for (int i = 0; i < vertical; i++)
	{
		gotoxy(coordX, coordY + i);
		cout << string(horizontal, ' ');
	}
	setColor(FG | BG);
	gotoxy(coordX + 1, coordY); cout << ch << ". ";
	breakLine(coordX + 4, coordY, s, 73);
}
void addButton2(string s, int coordX, int coordY, int horizontal, int vertical, int FG, int BG)
{
	setColor(BG);
	for (int i = 0; i < vertical; i++)
	{
		gotoxy(coordX, coordY + i);
		cout << string(horizontal, ' ');
	}
	setColor(FG | BG);
	gotoxy(coordX, coordY + vertical / 2);	cout << s;
}
void clearPartOfScreen(int coordX, int coordY, int horizontal, int vertical)
{
	setColor(0);
	for (int i = 0; i < vertical; i++)
	{
		gotoxy(coordX, coordY + i);
		cout << string(horizontal, ' ');
	}
}
void notification(string s, int coordX, int coordY, int horizontal, int vertical, int color)
{
	normal();
	drawRectangle(coordX, coordY, horizontal, vertical);
	gotoxy(coordX + 1, coordY + vertical / 2);  cout << string(horizontal - 2, ' ');
	setColor(color);
	alignCenter(s, coordX, coordY + vertical / 2, horizontal);
}
void notification1(string s, int x, int y, int horizontal, int vertical, int color) // login
{
	setColor(FOREGROUND_BRIGHTWHITE);
	drawRectangle(x, y, horizontal, vertical);
	gotoxy(x + 1, y + 1);
	for (int i = 0; i < horizontal - 2; i++)
	{
		cout << '.'; Sleep(4);
	}
	gotoxy(x + 1, y + 1);	
	setColor(color);
	cout << string(horizontal - 2, '.');
	alignCenter(s, x, y + 1, horizontal);
}
void drawTable1(int coordX, int coordY, int horizontal, int vertical)  //subjectList, classList
{
//	int x = 100, y = 7, horizontal = 98, vertical = 33;
// 	length: 1 7 1 29 1 58 1
	int h = (horizontal - 8) / 3;
	drawRectangle(coordX, coordY, horizontal, vertical);
	gotoxy(coordX + 8, coordY); cout << char(194);
	gotoxy(coordX + 8 + h, coordY);  cout << char(194);
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX + 8, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 8 + h, coordY + 1 + i); cout << char(179);
	}
	gotoxy(coordX + 8, coordY + vertical - 1); 	cout << char(193);
	gotoxy(coordX + 8 + h, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX, coordY + 2); 
	cout << char(195) << string(7, char(196)) << char(197) << string(h - 1, char(196))
		 << char(197) << string(horizontal - 8 - h - 2, char(196)) << char(180);
}
void table1(int x, int y, int horizontal, int vertical, string menu[4], int mode)  //SubjectList, ClassList 
{
	int h = (horizontal - 8) / 3;
	alignCenter(menu[0], x, y - 1, horizontal);
	drawTable1(x, y, horizontal, vertical);
	alignCenter(menu[1], x + 1, y + 1, 7);
	alignCenter(menu[2], x + 8, y + 1, h);
	alignCenter(menu[3], x + h + 8, y + 1, horizontal - h - 8);
	if (mode != 0)
	{
		gotoxy(x + 1, y + vertical);	
		cout << "ENTER: Hieu chinh\t\tDELETE: Xoa";
	}
}
void clearTable1(int x, int y, int horizontal, int vertical)
{
	int h = (horizontal - 8) / 3;
	clearPartOfScreen(x + 1, y + 3, 7, vertical - 4);
	clearPartOfScreen(x + 9, y + 3, h - 1, vertical - 4);
	clearPartOfScreen(x + h + 9, y + 3, horizontal - h - 10, vertical - 4);
	normal();
	for (int i = 0; i < 29; i++)
	{
		gotoxy(x + 8, y + 3 + i); cout << char(179);
		gotoxy(x + 8 + h, y + 3 + i); cout << char(179);
	}
}
void drawTable2()  // StudentList
{
//  length: 1 7 1 20 1 44 1 15 1 6 1	
	int coordX = 100, coordY = 7, horizontal = 98, vertical = 33;	
	drawRectangle(coordX, coordY, horizontal, vertical);
	gotoxy(coordX + 8, coordY); cout << char(194);
	gotoxy(coordX + 29, coordY); cout << char(194);
	gotoxy(coordX + 74, coordY); cout << char(194);
	gotoxy(coordX + 90, coordY); cout << char(194);
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX + 8, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 29, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 74, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 90, coordY + 1 + i); cout << char(179);
	}
	gotoxy(coordX + 8, coordY + vertical - 1); 	cout << char(193);
	gotoxy(coordX + 29, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX + 74, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX + 90, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX, coordY + 2);
	cout << char(195) << string(7, char(196)) << char(197) << string(20, char(196))
		 << char(197) << string(44, char(196)) << char(197) << string(15, char(196))
		 << char(197) << string(6, char(196)) << char(180);
}
void table2(string s, int mode)  // mode == 0: che do chi xem, mode != 0: co the chinh sua
{	
//  length: 1 7 1 20 1 44 1 15 1 6 1
	int x = 100, y = 7, horizontal = 98, vertical = 33;	
	string menu[6] = {"DANH SACH SINH VIEN LOP ",
					  "STT",
					  "MSSV",
					  "HO",
					  "TEN",
					  "PHAI"};
	drawTable2();
	alignCenter(menu[0] + s, x, y - 1, horizontal);
	alignCenter(menu[1], x + 1, y + 1, 7);
	alignCenter(menu[2], x + 9, y + 1, 20);
	alignCenter(menu[3], x + 30, y + 1, 44);
	alignCenter(menu[4], x + 75, y + 1, 15);
	alignCenter(menu[5], x + 91, y + 1, 6);
	if (mode != 0)
	{
		gotoxy(x + 1, y + vertical);	
		cout << "ENTER: Hieu chinh\t\tDELETE: Xoa";
	}
}
void clearTable2()
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;	
	clearPartOfScreen(x + 1, y + 3, 7, vertical - 4);
	clearPartOfScreen(x + 9, y + 3, 20, vertical - 4);
	clearPartOfScreen(x + 30, y + 3, 44, vertical - 4);
	clearPartOfScreen(x + 75, y + 3, 15, vertical - 4);
	clearPartOfScreen(x + 91, y + 3, 6, vertical - 4);
	normal();
	for (int i = 0; i < vertical - 4; i++)
	{
		gotoxy(x + 8, y + 3 + i); cout << char(179);
		gotoxy(x + 29, y + 3 + i); cout << char(179);
		gotoxy(x + 74, y + 3 + i); cout << char(179);
		gotoxy(x + 90, y + 3 + i); cout << char(179);
	}
}
drawTable3()  // score list
{
//  length: 1 7 1 20 1 44 1 15 1 10 1
	int coordX = 100, coordY = 7, horizontal = 102, vertical = 33;
	drawRectangle(coordX, coordY, horizontal, vertical);
	gotoxy(coordX + 8, coordY); cout << char(194);
	gotoxy(coordX + 29, coordY); cout << char(194);
	gotoxy(coordX + 74, coordY); cout << char(194);
	gotoxy(coordX + 90, coordY); cout << char(194);
	for (int i = 0; i < vertical - 2; i++)
	{
		gotoxy(coordX + 8, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 29, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 74, coordY + 1 + i); cout << char(179);
		gotoxy(coordX + 90, coordY + 1 + i); cout << char(179);
	}
	gotoxy(coordX + 8, coordY + vertical - 1); 	cout << char(193);
	gotoxy(coordX + 29, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX + 74, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX + 90, coordY + vertical - 1);	cout << char(193);
	gotoxy(coordX, coordY + 2);
	cout << char(195) << string(7, char(196)) << char(197) << string(20, char(196))
		 << char(197) << string(44, char(196)) << char(197) << string(15, char(196))
		 << char(197) << string(10, char(196)) << char(180);
}
void table3(Subject a, Class b) // score list
{
//  length: 1 7 1 20 1 44 1 15 1 10 1
	int x = 100, y = 7, horizontal = 102, vertical = 33;
	string menu[6] = {"DIEM THI MON ",
					  "STT",
					  "MSSV",
					  "HO",
					  "TEN",
					  "DIEM THI"};
	drawTable3();
	alignCenter(menu[0] + a.tenMh + " LOP " + b.maLop, x, y - 1, horizontal);
	alignCenter(menu[1], x + 1, y + 1, 7);
	alignCenter(menu[2], x + 9, y + 1, 20);
	alignCenter(menu[3], x + 30, y + 1, 44);
	alignCenter(menu[4], x + 75, y + 1, 15);
	alignCenter(menu[5], x + 91, y + 1, 10);
}
void clearTable3()  // score list
{
	//  length: 1 7 1 20 1 44 1 15 1 10 1
	int x = 100, y = 7, horizontal = 102, vertical = 33;
	clearPartOfScreen(x + 1, y + 3, 7, vertical - 4);
	clearPartOfScreen(x + 9, y + 3, 20, vertical - 4);
	clearPartOfScreen(x + 30, y + 3, 44, vertical - 4);
	clearPartOfScreen(x + 75, y + 3, 15, vertical - 4);
	clearPartOfScreen(x + 91, y + 3, 10, vertical - 4);
	normal();
	for (int i = 0; i < vertical - 4; i++)
	{
		gotoxy(x + 8, y + 3 + i); cout << char(179);
		gotoxy(x + 29, y + 3 + i); cout << char(179);
		gotoxy(x + 74, y + 3 + i); cout << char(179);
		gotoxy(x + 90, y + 3 + i); cout << char(179);
	}
}
void infoBar1(int x, int y, int horizontal, ClassList a, int i)
{
	int h = (horizontal - 8) / 3;
	alignCenter(to_string(i + 1), x + 1, y + 3, 7);
	alignCenter(a.lop[i].maLop, x + 9, y + 3, h - 1);
	alignCenter(a.lop[i].tenLop, x + h + 8, y + 3, horizontal - h - 8);
}
void infoBar2(int x, int y, int horizontal, SubjectList a, int i)
{
	int h = (horizontal - 8) / 3;
	alignCenter(to_string(i + 1), x + 1, y + 3, 7);
	alignCenter(a.mh[i]->maMh, x + 9, y + 3, h - 1);
	alignCenter(a.mh[i]->tenMh, x + h + 8, y + 3, horizontal - h - 8);
}
void infoBar3(int x, int y, StudentNode *p, int index)  // StudentList
{
	alignCenter(to_string(index + 1), x + 1, y + 3, 7);
	alignCenter(p->data.maSv, x + 9, y + 3, 20);
	alignCenter(p->data.ho, x + 30, y + 3, 44);
	alignCenter(p->data.ten, x + 75, y + 3, 15);
	alignCenter(p->data.phai, x + 91, y + 3, 6);
}
void infoBar3(int x, int y, StudentNode *p, int index, Subject a)  // StudentList + score
{
	alignCenter(to_string(index + 1), x + 1, y + 3, 7);
	alignCenter(p->data.maSv, x + 9, y + 3, 20);
	alignCenter(p->data.ho, x + 30, y + 3, 44);
	alignCenter(p->data.ten, x + 75, y + 3, 15);
	for (ScoreNode *temp = p->data.head; temp != NULL; temp = temp->next)
	{
		if (temp->data.maMh == a.maMh)
		{
			alignCenter(temp->data.diem, x + 91, y + 3, 10);
			return;
		}
	}
	alignCenter("Chua thi", x + 91, y + 3, 10);
}
void lightBar1(int x, int y, int horizontal, int color) // table1
{
	int h = (horizontal - 8) / 3;
	gotoxy(x + 1, y + 3);	
	setColor(color);
	cout << string(7, ' ') << char(179) << string(h - 1, ' ') << char(179)
		 << string(horizontal - 8 - h - 2, ' ');
}
void lightBar2(int x, int y, int horizontal, int color) // table2
{
	gotoxy(x + 1, y + 3);
	setColor(color);
	cout << string(7, ' ') << char(179) << string(20, ' ') << char(179) << string(44, ' ')
		 << char(179) << string(15, ' ') << char(179) << string(6, ' ');
}
void lightBar3(int x, int y, int horizontal, int color)  // table3, score
{
	gotoxy(x + 1, y + 3);
	setColor(color);
	cout << string(7, ' ') << char(179) << string(20, ' ') << char(179) << string(44, ' ')
		 << char(179) << string(15, ' ') << char(179) << string(10, ' ');	
}
void notificationBlock(string s, int x, int y, int horizontal, int color)
{
	int vertical = 5;
	clearPartOfScreen(x, y, horizontal, vertical);
	normal();
	drawRectangle(x, y, horizontal, vertical);	
	setColor(color);
	alignCenter(s, x, y + 2, horizontal);
	Sleep(700);
	clearPartOfScreen(x, y, horizontal, vertical);
}
void breakLine(int x, int y, string s, int bound)  // bound: gioi han ngat dong
{
	int remainder = s.length(), firstIndex = 0, curRow = 0;
	for (; remainder > bound; curRow++)
	{
		for (int i = firstIndex + bound - 1; ; i--)
		{
			if (s[i] == ' ')
			{
				gotoxy(x, y + curRow);
				for (int j = firstIndex; j <= i; j++)
					cout << s[j];
				remainder -= i - firstIndex + 1;
				firstIndex = i + 1;
				break;
			}
			else
			{
				if (i == firstIndex)
				{
					gotoxy(x, y + curRow);
					for (int j = firstIndex; j <= firstIndex + bound - 1; j++)
						cout << s[j];
					remainder -= bound;
					firstIndex = firstIndex + bound;
					break;
				}
			}
		}
	}
	gotoxy(x, y + curRow);
	for (int i = firstIndex; i < s.length(); i++)
		cout << s[i];	
}
bool verifyingDeleteBlock(int x, int y) 
{
	int horizontal = 46, vertical = 5;
	clearPartOfScreen(x, y, horizontal, vertical);
	normal();
	drawRectangle(x, y, horizontal, vertical);
	alignCenter("Ban co chac muon xoa khong?", x, y + 1, horizontal);
	int h = (horizontal - 17) / 2; // 5 + 5 + 7
	addButton("Co", x + h, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);  // khoang cach giua hai nut la 7
	addButton("Khong", x + h + 12, y + 3, 5, 1, 0, BACKGROUND_BRIGHTWHITE); // 5 + 7
	int curCol = 0;
	char ch;
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;
		if (ch == RIGHT || ch == LEFT)
		{
			if (curCol == 0)
			{
				addButton("Co", x + h, y + 3, 5, 1, 0, BACKGROUND_BRIGHTWHITE);
				curCol++;
				addButton("Khong", x + h + 12, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);
			}
			else
			{
				addButton("Co", x + h, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);
				curCol--;
				addButton("Khong", x + h + 12, y + 3, 5, 1, 0, BACKGROUND_BRIGHTWHITE);						
			}
		}
		if (ch == ENTER)
		{
			if (curCol == 0)
			{
				notificationBlock("Xoa thanh cong!", x, y, horizontal, FOREGROUND_LIGHTGREEN);
				return true;
			}
			else
			{
				clearPartOfScreen(x, y, horizontal, vertical);
				return false;
			}
		}
		if (ch == ESC)
		{
			clearPartOfScreen(x, y, horizontal, vertical);
			return false;
		}
	}
}
