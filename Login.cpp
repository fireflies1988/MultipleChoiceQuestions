#include "Login.h"
#include "Interface.h"
#include "Menu.h"
#include "InputHandling.h"
#include "Class.h"
#include "Student.h"
#include "Subject.h"
#include "Question.h"
#include "Score.h"

extern ClassList a;
//extern SubjectList b;
//QuestionNode *root = NULL;
//Stack idStack;
StudentNode *loginStudent;  // luu du lieu sinh vien dung dang nhap
Class classOfThisStudent;

string loginMenu[5] = {"DANG NHAP",
					   "Tai khoan: ",
					   "Mat khau: ",
					   "Dang nhap",
					   "Thoat"};
// userName: overflowIndex = 31, bound = 31
// password: overflowIndex = 31, bound = 31
bool manipulateLogin(int x, int y, int horizontal, int vertical) // true: GV, false: SV
{
	string userName, password;
	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
	char ch = inputHandling(userName, x + 4 + loginMenu[1].length(), y + 3, 31, 31, 1);
	bool on = false;
	while (true)
	{
		if (on)
		{
			if ((ch = getch()) == -32)	ch = getch();
			else	
				if (ch != ENTER) 	continue;	
		}
		else 	on = true;
		switch (ch)
		{
			case UP:
				if (curRow - 1 == -1)
				{
					normal();
					drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
					curRow = 3;
					addButton(loginMenu[4], x + 11, y + 11, 27, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow - 1 == 0)
					{
						normal();
						drawRectangle(x + 3 + loginMenu[1].length(), y + 5, horizontal - 3 - loginMenu[1].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
						ch = inputHandling(userName, x + 4 + loginMenu[1].length(), y + 3, 31, 31, 1);
						on = false;
					}
					else
					{
						if (curRow - 1 == 1)
						{
							addButton(loginMenu[3], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + loginMenu[1].length(), y + 5, horizontal - 3 - loginMenu[1].length() - 2, 3);
							ch = inputHandling(password, x + 4 + loginMenu[1].length(), y + 6, 31, 31, 0);
							on = false;	
						}
						else
						{
							if (curRow - 1 == 2)
							{
								addButton(loginMenu[4], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								addButton(loginMenu[3], x + 11, y + 9, 27, 1, 0, BACKGROUND_LIGHTCYAN); 
							}
						}
					}
				}
				break;
			case DOWN: 
				if (curRow + 1 == 4)
				{
					addButton(loginMenu[4], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
					ch = inputHandling(userName, x + 4 + loginMenu[1].length(), y + 3, 31, 31, 1);
					on = false;
				}
				else
				{
					if (curRow + 1 == 1)
					{
						normal();
						drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + loginMenu[1].length(), y + 5, horizontal - 3 - loginMenu[1].length() - 2, 3);
						ch = inputHandling(password, x + 4 + loginMenu[1].length(), y + 6, 31, 31, 0);
						on = false;
					}
					else
					{
						if (curRow + 1 == 2)
						{
							normal();
							drawRectangle(x + 3 + loginMenu[1].length(), y + 5, horizontal - 3 - loginMenu[1].length() - 2, 3);
							curRow++;
							addButton(loginMenu[3], x + 11, y + 9, 27, 1, 0, BACKGROUND_LIGHTCYAN);
						}
						else
						{
							if (curRow + 1 == 3)
							{
								addButton(loginMenu[3], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow++;
								addButton(loginMenu[4], x + 11, y + 11, 27, 1, 0, BACKGROUND_LIGHTCYAN);
							}
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
				if (curRow == 3)	
				{
					normal();
					system("cls");
					exit(0);
				}
				if (curRow == 2)
				{
					if (verifyAccount(userName, password))
					{
						Sleep(600);
						if (userName == "GV")
							return 1;
						return 0;
					}
				}
				break;
		}
	}
}
void login()
{
	int x = 80, y = 15, horizontal = 50, vertical = 14;
	// In DANG NHAP
	alignCenter(loginMenu[0], x, y - 1, horizontal);
	// Ve khung vien ngoai
	drawRectangle(x, y, horizontal, vertical);
	// loginMenu[1]
	gotoxy(x + 3, y + 3);	cout << loginMenu[1];
	drawRectangle(x + 3 + loginMenu[1].length(), y + 2, horizontal - 3 - loginMenu[1].length() - 2, 3);
	// loginMenu[2]
	gotoxy(x + 3, y + 6); 	cout << loginMenu[2];
	drawRectangle(x + 3 + loginMenu[1].length(), y + 5, horizontal - 3 - loginMenu[1].length() - 2, 3);
	// loginMenu[3], loginMenu[4]
	addButton(loginMenu[3], x + 11, y + 9, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
	addButton(loginMenu[4], x + 11, y + 11, 27, 1, 0, BACKGROUND_BRIGHTWHITE);
	if (manipulateLogin(x, y, horizontal, vertical))
		menu();
	studentView();
}
bool verifyAccount(string userName, string password)
{
	int x = 80, y = 29, horizontal = 50, vertical = 3;
	if (userName == "GV" && password == "GV")
	{
		notification1("Dang nhap thanh cong", x, y, horizontal, vertical, FOREGROUND_LIGHTGREEN);
		return true;
	}
	if (userName == "" || password == "")
	{
		notification("Tai khoan va mat khau khong duoc bo trong!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	for (int i = 0; i < a.n; i++)
	{
		for (StudentNode *temp = a.lop[i].head; temp != NULL; temp = temp->next)
		{
			if (userName == temp->data.maSv && password == temp->data.password)
			{
				loginStudent = temp;
				classOfThisStudent = a.lop[i];
				notification1("Dang nhap thanh cong", x, y, horizontal, vertical, FOREGROUND_LIGHTGREEN);
				return true;
			}
		}
	}
	notification1("Tai khoan hoac mat khau khong chinh xac", x, y, horizontal, vertical, FOREGROUND_RED);
	return false;
}

