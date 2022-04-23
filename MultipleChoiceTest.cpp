#include "MultipleChoiceTest.h"
#include "Interface.h"
#include "InputHandling.h"
#include <cmath>
#include <iomanip>
#include "Subject.h"
#include "Score.h"

extern StudentNode *loginStudent;
extern Class classOfThisStudent;

bool verifyingSubmitBlock(int &hours, int &minutes, int &seconds, bool &warning, clock_t &start) // 1: enter, 2: esc, 3: timeout
{
	int x = 58 + (140 - 50) / 2, y = 2 + (44 - 5) / 2, horizontal = 50, vertical = 5;
	clearPartOfScreen(x, y, horizontal, vertical);
	normal();
	drawRectangle(x, y, horizontal, vertical);
	alignCenter("Ban co chac muon nop bai khong?", x, y + 1, horizontal);
	int h = (horizontal - 20) / 2; // 5 + 5 + 10
	addButton("Co", x + h, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);  // khoang cach giua hai nut la 7
	addButton("Khong", x + h + 15, y + 3, 5, 1, 0, BACKGROUND_BRIGHTWHITE); // 5 + 7
	int curCol = 0;
	char ch;
	while (hours != -1)
	{
		while (double(clock() - start) / CLOCKS_PER_SEC < 1)
		{
			if (kbhit())
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
						addButton("Khong", x + h + 15, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);
					}
					else
					{
						addButton("Co", x + h, y + 3, 5, 1, 0, BACKGROUND_LIGHTCYAN);
						curCol--;
						addButton("Khong", x + h + 15, y + 3, 5, 1, 0, BACKGROUND_BRIGHTWHITE);						
					}
				}
				if (ch == ENTER)
				{
					clearPartOfScreen(x, y, horizontal, vertical);
					if (curCol == 0)	return true;
					else	return false;
				}
				if (ch == ESC)
				{
					clearPartOfScreen(x, y, horizontal, vertical);
					return false;
				}
			}
		}
		updateTimer(hours, minutes, seconds, warning);
		start = clock();
	}
	clearPartOfScreen(x, y, horizontal, vertical);
	return true;
}
bool resultBlock(char picked[], char answer[], int soCauHoi, int soPhut, Subject a, Stack subjectIdStack, int mode)
{
	int x = 58 + (140 - 50) / 2, y = 2 + (44 - 9) / 2, horizontal = 50, vertical = 9;
	int correctAnswer = 0;
	for (int i = 0; i < soCauHoi; i++)
	{
		if (picked[i] == answer[i])	
			correctAnswer++;
	}
	double grade = (10.0 / soCauHoi) * correctAnswer;
	if (mode != 0)
	{
		updateScore(a, loginStudent->data.head, grade);
		saveScoreList(classOfThisStudent, a);
		saveMultipleChoiceTest(a, loginStudent, picked, answer, soCauHoi, soPhut, subjectIdStack);
	}
	clearPartOfScreen(x, y, horizontal, vertical);
	normal();
	drawRectangle(x, y, horizontal, vertical);
	alignCenter("Ban tra loi dung " + to_string(correctAnswer) + " cau. Ban duoc: ", grade, " diem.", x, y + 2, horizontal);
	addButton("Xem bai thi", x + 12, y + 4, 26, 1, 0, BACKGROUND_LIGHTCYAN);
	addButton("Thoat", x + 12, y + 6, 26, 1, 0, BACKGROUND_BRIGHTWHITE);
	int curRow = 0;
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;	
		if (ch == UP || ch == DOWN)
		{
			if (curRow == 0)
			{
				addButton("Xem bai thi", x + 12, y + 4, 26, 1, 0, BACKGROUND_BRIGHTWHITE);
				curRow++;
				addButton("Thoat", x + 12, y + 6, 26, 1, 0, BACKGROUND_LIGHTCYAN);
			}
			else
			{
				addButton("Xem bai thi", x + 12, y + 4, 26, 1, 0, BACKGROUND_LIGHTCYAN);
				curRow--;
				addButton("Thoat", x + 12, y + 6, 26, 1, 0, BACKGROUND_BRIGHTWHITE);
			}
		}
		if (ch == ENTER)
		{
			if (curRow == 0)
			{
				clearPartOfScreen(x, y, horizontal, vertical);
				return true;
			}
			else
			{
				clearPartOfScreen(x, y, horizontal, vertical);
				return false;
			}
		}	
	}
}
bool checkRequirement(QuestionNode *root, int soCauHoi, int soPhut, Subject a)
{
	int x = 104, y = 26, horizontal = 50, vertical = 3;
	int availableQuestion = getNumberOfNode(root, 0, a);
	if (to_string(soCauHoi) == "0" || to_string(soPhut) == "0")
	{
		clearPartOfScreen(x, y, horizontal, 4);
		notification("Khong duoc bo trong bat ky phan nao!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	if (soPhut > 3600)
	{
		clearPartOfScreen(x, y, horizontal, 4);
		notification("So phut toi da la 3600. Moi ban nhap lai!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	if (availableQuestion < soCauHoi)
	{
		clearPartOfScreen(x, y, horizontal, 3);
		normal();
		drawRectangle(x, y, horizontal, 4);
		setColor(FOREGROUND_RED);
		alignCenter("Thieu cau hoi, so cau hoi hien co la " + to_string(availableQuestion) + ".", x, y + 1, horizontal);
		alignCenter("Moi ban nhap lai!", x, y + 2, horizontal);
		return false;
	}
	return true;
}
bool input(QuestionNode *root, Subject a, int &soCauHoi, int &soPhut)
{
	int x = 104, y = 12, horizontal = 50, vertical = 14;
	string menu[4] = {"So cau hoi thi: ",
					  "So phut thi: ",
					  "Bat dau thi",
					  "Tro ve"};
	normal();
	drawRectangle(x, y, horizontal, vertical);
	gotoxy(x + 3, y + 3); 	cout << menu[0];
	drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);	
	gotoxy(x + 3, y + 6); 	cout << menu[1];
	drawRectangle(x + 3 + menu[0].length(), y + 5, horizontal - 3 - menu[0].length() - 2, 3);	
	addButton(menu[2], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
	addButton(menu[3], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);

	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);
	char ch = inputDigitOnly(soCauHoi, x + 4 + menu[0].length(), y + 3, 2);
	bool on = false;
	while (1)
	{
		if (on)
		{
			if ((ch = getch()) == -32)	ch = getch();
			else	
				if (ch != ENTER && ch != ESC) 	continue;	
		}
		else 	on = true;	
		switch(ch)
		{
			case UP:
				if (curRow == 0)
				{
					normal();
					drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);
					curRow = 3;
					addButton(menu[3], x + 11, y + 11, 27, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow == 1)
					{
						normal();
						drawRectangle(x + 3 + menu[0].length(), y + 5, horizontal - 3 - menu[0].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);
						ch = inputDigitOnly(soCauHoi, x + 4 + menu[0].length(), y + 3, 2);
						on = false;
					}
					else
					{
						if (curRow == 2)
						{
							addButton(menu[2], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + menu[0].length(), y + 5, horizontal - 3 - menu[0].length() - 2, 3);
							ch = inputDigitOnly(soPhut, x + 4 + menu[0].length(), y + 6, 4);
							on = false;
						}
						else
						{
							addButton(menu[3], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							addButton(menu[2], x + 11, y + 9, 27, 1, 0, BACKGROUND_LIGHTCYAN);
						}
					}
				}
				break;
			case DOWN:
				if (curRow == 3)
				{
					addButton(menu[3], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);	
					ch = inputDigitOnly(soCauHoi, x + 4 + menu[0].length(), y + 3, 2);
					on = false;
				}	
				else
				{
					if (curRow == 0)
					{
						normal();
						drawRectangle(x + 3 + menu[0].length(), y + 2, horizontal - 3 - menu[0].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + menu[0].length(), y + 5, horizontal - 3 - menu[0].length() - 2, 3);
						ch = inputDigitOnly(soPhut, x + 4 + menu[0].length(), y + 6, 4);
						on = false;
					}
					else
					{
						if (curRow == 1)
						{
							normal();
							drawRectangle(x + 3 + menu[0].length(), y + 5, horizontal - 3 - menu[0].length() - 2, 3);
							curRow++;
							addButton(menu[2], x + 11, y + 9, 27, 1, 0, BACKGROUND_LIGHTCYAN);
						}
						else
						{
							addButton(menu[2], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow++;
							addButton(menu[3], x + 11, y + 11, 27, 1, 0, BACKGROUND_LIGHTCYAN);
						}
					}
				}
				break;
			case ENTER:
				if (curRow == 0 || curRow == 1)
				{
					ch = DOWN;
					on = false;
				}
				if (curRow == 2)
				{
					if (checkRequirement(root, soCauHoi, soPhut, a))
					{
						clearPartOfScreen(x, y, horizontal, vertical + 5);
						return true;
					}
				}
				if (curRow == 3)
				{
					clearPartOfScreen(x, y, horizontal, vertical + 5);
					return false;	
				}
				break;
			case ESC:
				clearPartOfScreen(x, y, horizontal, vertical + 5);
				return false;
		}	
	}
}
void convertTime(int time, int &hours, int &minutes, int &seconds)
{
	seconds = 0;
	minutes = time % 60;
	hours = time / 60;
}
void timer(int hours, int minutes, int seconds)
{
	int x = 131, y = 7;
	setColor(FOREGROUND_LIGHTCYAN);
	if (hours == 0 && minutes < 1)	setColor(FOREGROUND_RED);
	gotoxy(x, y);
	cout << setfill('0') << setw(2) << hours << ':' << setw(2) << minutes << ':' << setw(2) << seconds;
}
void updateTimer(int &hours, int &minutes, int &seconds, bool &warning)
{
	int x = 131, y = 7;
	if (warning)	setColor(FOREGROUND_RED);
	else	setColor(FOREGROUND_LIGHTCYAN);
	if (--seconds == -1)
	{
		seconds = 59;
		if (--minutes == -1)
		{
			minutes = 59;
			if (--hours == -1)	return;
			gotoxy(x, y); 	cout << setw(2) << hours;
		}
		gotoxy(x + 3, y); 	cout << setw(2) << minutes;
	}
	if (hours == 0 && minutes < 1 && warning == false)
	{
		warning = true;
		timer(hours, minutes, seconds);
		return;
	}	
	gotoxy(x + 6, y);	cout << setw(2) << seconds;
}
void shuffleIdStack(Stack &st)
{
	srand(time(NULL));
	for (int i = 0; i < st.n; i++)
	{
		int r = rand() % st.n;
		int temp = st.node[i];
		st.node[i] = st.node[r];
		st.node[r] = temp;
	}
}
void saveMultipleChoiceTest(Subject b, StudentNode *p, char picked[], char answer[], int soCauHoi, int soPhut, Stack subjectIdStack)
{
	ofstream outFile("BAITHI_" + b.maMh + "_" + p->data.maSv + ".txt");
	outFile << soCauHoi << " " << soPhut << " " << subjectIdStack.n << endl;
	for (int i = 0; i < soCauHoi; i++)
		outFile << picked[i] << " ";
	outFile << endl;
	for (int i = 0; i < soCauHoi; i++)
		outFile << answer[i] << " ";
	outFile << endl;
	for (int i = 0; i < subjectIdStack.n; i++)
		outFile << subjectIdStack.node[i] << " ";
	outFile.close();
}
void loadMultipleChoiceTest(Subject b, StudentNode *p, char picked[], char answer[], int &soCauHoi, int &soPhut, Stack &subjectIdStack)
{
	ifstream inFile("BAITHI_" + b.maMh + "_" + p->data.maSv + ".txt");
	inFile >> soCauHoi >> soPhut >> subjectIdStack.n;
	for (int i = 0; i < soCauHoi; i++)
		inFile >> picked[i];
	for (int i = 0; i < soCauHoi; i++)
		inFile >> answer[i];
	for (int i = 0; i < subjectIdStack.n; i++)
		inFile >> subjectIdStack.node[i];
	inFile.close();
}
void reviewTest1(QuestionNode *root, StudentNode *p, Class a, Subject b)
{
	int soCauHoi, soPhut;
	char picked[100], answer[100];
	Stack subjectIdStack;
	loadMultipleChoiceTest(b, p, picked, answer, soCauHoi, soPhut, subjectIdStack);
	int x = 58, y = 2, horizontal = 140, vertical = 44;
	drawRectangle1(x, y, horizontal, vertical, BACKGROUND_BRIGHTWHITE);
	normal();
	gotoxy(x + 59 + 5, y + 3);	cout << "BAI THI TRAC NGHIEM MON: ";
	setColor(FOREGROUND_LIGHTCYAN);		cout << b.tenMh;
	normal();
	gotoxy(x + 59 + 5, y + 4); 	cout << "Thoi gian thi: ";
	setColor(FOREGROUND_LIGHTCYAN); 	cout << soPhut << " phut";
	normal();
	drawRectangle(x + 5, y + 2, 54, 5);
	string studentInfo[3] = {"Ho va ten: ",
							 "MSSV: ",
							 "Lop: "};
	for (int i = 0; i < 3; i++)
	{
		gotoxy(x + 6, y + 3 + i);	
		cout << studentInfo[i];
	}	
	setColor(FOREGROUND_LIGHTCYAN);
	gotoxy(x + 6 + studentInfo[0].length(), y + 3);
	cout << p->data.ho << " " << p->data.ten;
	gotoxy(x + 6 + studentInfo[1].length(), y + 4);
	cout << p->data.maSv;
	gotoxy(x + 6 + studentInfo[2].length(), y + 5);
	cout << a.maLop;
	normal();
	drawRectangle(x + 5, y + 7, 32, 4);
	alignCenter("DIEM THI", x + 5, y + 8, 30);
	for (int i = 0, temp = soCauHoi, stt = 0; i < ceil(soCauHoi / 28.0); i++)
	{
		if (temp > 28)
		{
			drawRectangle(x + 5 + 8 * i, y + 12, 8, 28 + 2);
			for (int j = 0; j < 28; j++)
			{
				gotoxy(x + 6 + 8 * i, y + 13 + j);
				cout << ++stt << " - ";
			}
			temp -= 28;
		}
		else
		{
			drawRectangle(x + 5 + 8 * i, y + 12, 8, temp + 2);
			for (int j = 0; j < temp; j++)
			{
				gotoxy(x + 6 + 8 * i, y + 13 + j);
				cout << ++stt << " - ";
			}
		}
	}
	gotoxy(x + 6, y + 11);	cout << "So luong cau hoi: ";
	setColor(FOREGROUND_LIGHTCYAN);
	cout << soCauHoi;	
	reviewTest(root, subjectIdStack, soCauHoi, picked, answer);
}
void reviewTest(QuestionNode *root, Stack subjectIdStack, int soCauHoi, char picked[], char answer[])
{
	int x = 58, y = 2, horizontal = 140, vertical = 44;
	clearPartOfScreen(x + 48 + 23, y + 34, 30, 3);
	clearPartOfScreen(x + 59 + 5, y + 5, strlen("Con lai: ") + 10, 1);
	setColor(FOREGROUND_LIGHTGREEN);
	gotoxy(x + 59 + 5, y + 5);
	cout << "Ban dang o che do xem bai thi";
	int correctAnswer = 0;
	for (int i = 0; i < soCauHoi; i++)
	{
		if (picked[i] == answer[i])
			correctAnswer++;
	}
	double grade = (10.0 / soCauHoi) * correctAnswer;
	setColor(FOREGROUND_LIGHTRED);
	alignCenter(grade, x + 5, y + 9, 30);
	normal();
	drawRectangle(x + 48 + 14, y + 34, 49, 3);
	setColor(FOREGROUND_LIGHTGREEN);
	alignCenter("Ban tra loi dung duoc " + to_string(correctAnswer) + " tren tong so " + to_string(soCauHoi) + " cau.", x + 48 + 14, y + 35, 49);
	setColor(FOREGROUND_YELLOW);
	gotoxy(x + 49, y + vertical - 3);	cout << "<--- OR --->: Chuyen cau hoi";
	gotoxy(x + horizontal - 16, y + vertical - 3);	cout << string(12, ' ');
	gotoxy(x + horizontal - 15, y + vertical - 3);	cout << "ESC: Thoat";
	for (int i = 0, temp = soCauHoi, stt = 0; i < ceil(soCauHoi / 28.0); i++)
	{
		if (temp > 28)
		{
			for (int j = 0; j < 28; j++, stt++)
			{
				if (picked[stt] == answer[stt])
					addButton2(to_string(stt + 1) + " - " + picked[stt], x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_LIGHTGREEN);
				if (picked[stt] == '@')
					addButton2(to_string(stt + 1) + " - ", x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_RED);
				else
					if (picked[stt] != answer[stt])
						addButton2(to_string(stt + 1) + " - " + picked[stt], x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_RED);
			}
			temp -= 28;
		}
		else
		{
			for (int j = 0; j < temp; j++, stt++)
			{
				if (picked[stt] == answer[stt])
					addButton2(to_string(stt + 1) + " - " + picked[stt], x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_LIGHTGREEN);
				if (picked[stt] == '@')
					addButton2(to_string(stt + 1) + " - ", x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_RED);
				else
					if (picked[stt] != answer[stt])
						addButton2(to_string(stt + 1) + " - " + picked[stt], x + 6 + 8 * i, y + 13 + j, 6, 1, 0, BACKGROUND_RED);
			}
		}
	}
	int index = 0;
	string option[4];
	QuestionNode *temp = searchQuestion(root, subjectIdStack.node[index]);
	saveOptions(option, temp);
	printQuestion(temp, index, 4);
	addButton1(option[answer[index] - 'A'], answer[index], x + 48, y + 23 + 2 * (answer[index] - 'A'), 77, option[answer[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTRED);
	if (picked[index] != '@')
		addButton1(option[picked[index] - 'A'], picked[index], x + 48, y + 23 + 2 * (picked[index] - 'A'), 77, option[picked[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC)	continue;
		switch(ch)
		{
			case LEFT:
				if (index == 0)		index = soCauHoi - 1;
				else	index--;
				temp = searchQuestion(root, subjectIdStack.node[index]);
				saveOptions(option, temp);
				printQuestion(temp, index, 4);
				if (answer[index] != picked[index])
					addButton1(option[answer[index] - 'A'], answer[index], x + 48, y + 23 + 2 * (answer[index] - 'A'), 77, option[answer[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTRED);
				if (picked[index] != '@')
					addButton1(option[picked[index] - 'A'], picked[index], x + 48, y + 23 + 2 * (picked[index] - 'A'), 77, option[picked[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
				break;
			case RIGHT:
				if (index == soCauHoi - 1)	index = 0;
				else	index++;
				temp = searchQuestion(root, subjectIdStack.node[index]);
				saveOptions(option, temp);
				printQuestion(temp, index, 4);
				if (answer[index] != picked[index])
					addButton1(option[answer[index] - 'A'], answer[index], x + 48, y + 23 + 2 * (answer[index] - 'A'), 77, option[answer[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTRED);
				if (picked[index] != '@')
					addButton1(option[picked[index] - 'A'], picked[index], x + 48, y + 23 + 2 * (picked[index] - 'A'), 77, option[picked[index] - 'A'].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
				break;
			case ESC:
				clearPartOfScreen(x, y, horizontal, vertical + 4);
				return;
		}
	}
}
void multipleChoiceTest(Subject a, QuestionNode *root, int soCauHoi, int soPhut, int mode) // mode == 0: gv, mode != 0: SV 
{
	int x = 58, y = 2, horizontal = 140, vertical = 44;
	drawRectangle1(x, y, horizontal, vertical, BACKGROUND_BRIGHTWHITE);
	normal();
	gotoxy(x + 59 + 5, y + 3);	cout << "BAI THI TRAC NGHIEM MON: ";
	setColor(FOREGROUND_LIGHTCYAN);		cout << a.tenMh;
	normal();
	gotoxy(x + 59 + 5, y + 4); 	cout << "Thoi gian thi: ";
	setColor(FOREGROUND_LIGHTCYAN); 	cout << soPhut << " phut";
	int hours, minutes, seconds;
	convertTime(soPhut, hours, minutes, seconds);
	normal();
	gotoxy(x + 59 + 5, y + 5);	cout << "Con lai: ";
	timer(hours, minutes, seconds);
	normal();
	drawRectangle(x + 5, y + 2, 54, 5);
	string studentInfo[3] = {"Ho va ten: ",
							 "MSSV: ",
							 "Lop: "};
	for (int i = 0; i < 3; i++)
	{
		gotoxy(x + 6, y + 3 + i);	
		cout << studentInfo[i];
		if (mode == 0)
		{
			setColor(FOREGROUND_LIGHTCYAN);
			cout << "Che do giao vien";
			normal();
		}
	}
	if (mode)
	{
		setColor(FOREGROUND_LIGHTCYAN);
		gotoxy(x + 6 + studentInfo[0].length(), y + 3);
		cout << loginStudent->data.ho << " " << loginStudent->data.ten;
		gotoxy(x + 6 + studentInfo[1].length(), y + 4);
		cout << loginStudent->data.maSv;
		gotoxy(x + 6 + studentInfo[2].length(), y + 5);
		cout << classOfThisStudent.maLop;
		normal();
	}
	setColor(FOREGROUND_YELLOW);
	gotoxy(x + 49, y + vertical - 3);	cout << "<--- OR --->: Chuyen cau hoi";
	gotoxy(x + horizontal - 16, y + vertical - 3);	cout << "ENTER: Chon";
	normal();
	drawRectangle(x + 5, y + 7, 32, 4);
	alignCenter("DIEM THI", x + 5, y + 8, 30);	
	for (int i = 0, temp = soCauHoi, stt = 0; i < ceil(soCauHoi / 28.0); i++)
	{
		if (temp > 28)
		{
			drawRectangle(x + 5 + 8 * i, y + 12, 8, 28 + 2);
			for (int j = 0; j < 28; j++)
			{
				gotoxy(x + 6 + 8 * i, y + 13 + j);
				cout << ++stt << " - ";
			}
			temp -= 28;
		}
		else
		{
			drawRectangle(x + 5 + 8 * i, y + 12, 8, temp + 2);
			for (int j = 0; j < temp; j++)
			{
				gotoxy(x + 6 + 8 * i, y + 13 + j);
				cout << ++stt << " - ";
			}
		}
	}
	gotoxy(x + 6, y + 11);	cout << "So luong cau hoi: ";
	setColor(FOREGROUND_LIGHTCYAN);
	cout << soCauHoi;
	addButton("NOP BAI", x + 48 + 23, y + 34, 30, 3, 0, BACKGROUND_BRIGHTWHITE);
	Stack subjectIdStack;
	saveId(root, subjectIdStack, a);
	shuffleIdStack(subjectIdStack);
	int index = 0, curRow = 0;
	bool warning = false;
	char answer[soCauHoi], picked[soCauHoi];  // mang luu dap an da chon tai cau index + 1;
	for (int i = 0; i < soCauHoi; i++)
	{
		QuestionNode *temp = searchQuestion(root, subjectIdStack.node[i]);
		answer[i] = temp->data.dapAn;
	}
	QuestionNode *temp = searchQuestion(root, subjectIdStack.node[index]);
	string option[4];
	saveOptions(option, temp);
	printQuestion(temp, index, curRow);
	for (int i = 0; i < soCauHoi; i++)
		picked[i] = '@';  // gan tam
	int pickedRow[soCauHoi];
	while (hours != -1)
	{
		clock_t start = clock();
		while (double(clock() - start) / CLOCKS_PER_SEC < 1)
		{
			if (kbhit())
			{
				char ch = getch();
				if (ch == -32)	ch = getch();
				else
					if (ch != ENTER)	continue;
				switch(ch)
				{
					case UP:
						if (curRow == 0)
						{
							addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, FOREGROUND_WHITE, 0);
							if (picked[index] == 'A' + curRow) // kiem tra xem cau nay da duoc chon dap an chua	
								addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
							curRow = 4;
							addButton("NOP BAI", x + 48 + 23, y + 34, 30, 3, 0, BACKGROUND_LIGHTCYAN);
						}
						else
						{
							if (curRow == 4)
							{
								addButton("NOP BAI", x + 48 + 23, y + 34, 30, 3, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTCYAN);
							}
							else
							{
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, FOREGROUND_WHITE, 0);
								if (picked[index] == 'A' + curRow) 
									addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
								curRow--;
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTCYAN);
							}
						}
						break;
					case DOWN:
						if (curRow == 3)
						{
							addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, FOREGROUND_WHITE, 0);
							if (picked[index] == 'A' + curRow) 
								addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
							curRow++;
							addButton("NOP BAI", x + 48 + 23, y + 34, 30, 3, 0, BACKGROUND_LIGHTCYAN);
						}
						else
						{
							if (curRow == 4)
							{
								addButton("NOP BAI", x + 48 + 23, y + 34, 30, 3, 0, BACKGROUND_BRIGHTWHITE);
								curRow = 0;
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTCYAN);
							}
							else
							{
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, FOREGROUND_WHITE, 0);
								if (picked[index] == 'A' + curRow) 
									addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
								curRow++;
								addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTCYAN);
							}
						}
						break;
					case LEFT:
						if (curRow != 4)
						{
							if (index == 0)		index = soCauHoi - 1;
							else	index--;
							curRow = 0;
							temp = searchQuestion(root, subjectIdStack.node[index]);
							saveOptions(option, temp);
							printQuestion(temp, index, curRow);
							if (picked[index] != 'A' && picked[index] != '@')
								addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
						}
						break;
					case RIGHT:
						if (curRow != 4)
						{
							if (index == soCauHoi - 1)	index = 0;
							else	index++;
							curRow = 0;
							temp = searchQuestion(root, subjectIdStack.node[index]);
							saveOptions(option, temp);
							printQuestion(temp, index, curRow);
							if (picked[index] != 'A' && picked[index] != '@')
								addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, option[pickedRow[index]].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTYELLOW);
						}
						break;
					case ENTER:
						if (curRow != 4)
						{
							printQuestion(temp, index, curRow);
							picked[index] = 'A' + curRow;
							pickedRow[index] = curRow;
							int cotDapAn;
							if (index % 28 != 0)	cotDapAn = ceil(index / 28.0) - 1;
							else	cotDapAn = index / 28;
							int hangDapAn = index - 28 * cotDapAn;
							addButton2(to_string(index + 1) + " - " + picked[index], x + 6 + 8 * cotDapAn, y + 13 + hangDapAn, 6, 1, 0, BACKGROUND_LIGHTYELLOW);
						}
						else
						{
							if (verifyingSubmitBlock(hours, minutes, seconds, warning, start))
							{
								if (resultBlock(picked, answer, soCauHoi, soPhut, a, subjectIdStack, mode))
								{
									reviewTest(root, subjectIdStack, soCauHoi, picked, answer);
									return;
								}
								else
								{
									clearPartOfScreen(x, y, horizontal, vertical);
									return;
								}
							}
							else
							{
								printQuestion(temp, index, curRow);
								if (picked[index] != '@')
									addButton1(option[pickedRow[index]], picked[index], x + 48, y + 23 + 2 * pickedRow[index], 77, 1, 0, BACKGROUND_LIGHTYELLOW);
							}
						}
						break;
				}
			}
		}
		updateTimer(hours, minutes, seconds, warning);
	}
	if (resultBlock(picked, answer, soCauHoi, soPhut, a, subjectIdStack, mode))
	{
		reviewTest(root, subjectIdStack, soCauHoi, picked, answer);
		return;
	}
	else
	{
		clearPartOfScreen(x, y, horizontal, vertical);
		return;
	}
//	int soCauHoi, phut, correctAnswer = 0; 
//	char answer;
//	for (int i = 0; i < a.n; i++)
//	{
//		cout << "So cau hoi thi: "; cin >> soCauHoi;
//		cout << "So phut thi: "; cin >> phut;
//		Stack st;
//		shuffleIdStack(idStack, st);
//		for (int i = 0; i < soCauHoi; i++)
//		{
//			cout << "Cau " << i + 1 << ": ";
//			QuestionNode *temp = searchQuestion(root, st.node[i]);
//			printQuestion(temp);
//			cout << "Chon dap an: "; cin >> answer; 
//			if (answer == temp->data.dapAn)	correctAnswer++;
//		}
//		cout << setprecision(2);
//		cout << "Ban tra loi dung " << correctAnswer << " cau. Ban duoc: " << (10.0 / soCauHoi) * correctAnswer << " diem." << endl;
//		break;
//	}
}
