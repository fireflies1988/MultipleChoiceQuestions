#include "Student.h"
#include "Interface.h"
#include "InputHandling.h"
#include "Score.h"

// overflowIndex = 51
// maSv: bound = 20
// ho: bound = 44
// ten: bound = 15
extern SubjectList b;
extern ClassList a;
bool checkStudentCode(Student sv, int mode) // mode == 0: Them sinh vien thanh cong!, mode != 0: Luu thay doi thanh cong!
{
	int x = 110, y = 31, horizontal = 70, vertical = 3;	
	for (int i = 0; i < a.n; i++)
	{
		for (StudentNode *temp = a.lop[i].head; temp != NULL; temp = temp->next)
		{
			if (sv.maSv == temp->data.maSv)
			{
				notification("Ma sinh vien da ton tai. Moi ban nhap lai!", x, y, horizontal, vertical, FOREGROUND_RED);
				return false;
			}
		}
	}
	if (sv.maSv == "" || sv.ho == "" || sv.ten == "" || sv.password == "")
	{
		notification("Khong duoc bo trong bat ky phan nao!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	else
	{
		notification(mode == 0 ? "Them sinh vien thanh cong!" : "Luu thay doi thanh cong!", x, y, horizontal, vertical, FOREGROUND_LIGHTGREEN);
		return true;
	}
}
void studentTable(string menu[9])
{
	int x = 110, y = 7, horizontal = 70, vertical = 24;
	normal();
	alignCenter(menu[0], x, y - 1, horizontal);  // tieu de
	drawRectangle(x, y, horizontal, vertical);	// khung vien
	// maSV, ho, ten, matkhau
	for (int i = 1; i < 5; i++)
	{
		gotoxy(x + 3, y + 3 * i); cout << menu[i];
		drawRectangle(x + 3 + menu[5].length(), y - 1 + 3 * i, horizontal - 3 - menu[5].length() - 2, 3);
	}	
	// gioi tinh
	gotoxy(x + 3, y + 15); cout << menu[5];
	addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
	addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
	// them sinh vien, hien thi mat khau, tro ve
	for (int i = 6, j = 0; i < 9; i++, j++)
		addButton(menu[i], x + 16, y + 17 + 2 * j, 38, 1, 0, BACKGROUND_BRIGHTWHITE); // horizontal - 2 * 16	
}
char chooseSex(bool &isMale) // true: Nam, false: Nu
{
	int x = 110, y = 7, horizontal = 70, vertical = 24;
	int curCol = 0;
	char ch;
	addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTCYAN);
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;
		if (ch == RIGHT || ch == LEFT)
		{
			if (isMale)
			{
				if (curCol == 0)
				{
					addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
					addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTCYAN);
					curCol++;
				}
				else
				{
					addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTCYAN);
					addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
					curCol--;
				}
			}
			else
			{
				if (curCol == 0)
				{
					addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
					addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTCYAN);
					curCol++;
				}
				else
				{
					addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTCYAN);
					addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
					curCol--;
				}
			}
		}	
		if (ch == ENTER)
		{
			if (curCol == 0 && !isMale)
			{
				addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
				isMale = true;
			}
			if (curCol == 1 && isMale)
			{
				addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);	
				isMale = false;			
			}
		}
		if (ch == UP || ch == DOWN || ch == ESC)	return ch;
	}
}
void addStudent(StudentNode *&p) // index la chi so lop
{
	int x = 110, y = 7, horizontal = 70, vertical = 24;
	string addStudentMenu[9] = {"THEM SINH VIEN",
								"MSSV: ",
								"Ho: ",
								"Ten: ",
								"Mat khau: ",
								"Gioi tinh: ",
								"Them sinh vien",
								"Hien thi mat khau",
								"Tro ve"};
	studentTable(addStudentMenu);
	Student sv;
	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
	char ch = inputCode(sv.maSv, x + 4 + addStudentMenu[5].length(), y + 3, 20);
	bool on = false, isMale = true, isShowPassword = false;
	sv.phai = "Nam";
	while (true)
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
				if (curRow - 1 == -1)
				{
					normal();
					drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
					curRow = 7;
					addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 2, 38, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow > 0 && curRow < 4)
					{
						normal();
						drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
						if (curRow == 0)	ch = inputCode(sv.maSv, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 20);
						if (curRow == 1)	ch = inputStdName(sv.ho, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 44);
						if (curRow == 2)	ch = inputStdName(sv.ten, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 15);
						on = false;
					}
					else
					{
						if (curRow == 4)
						{
							if (isMale)		
							{
								sv.phai = "Nam";
								addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
								addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
							}
							else	
							{
								sv.phai = "Nu";	
								addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
								addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);					
							}
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
							ch = inputHandling1(sv.password, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 31, 31, isShowPassword);
							on = false;
						}
						else
						{
							if (curRow == 5)
							{
								addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 0, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								ch = chooseSex(isMale);
								on = false;
							}
							else
							{
								if (curRow == 6 || curRow == 7)
								{
									addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow--;
									addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case DOWN:
				if (curRow + 1 == 8)
				{
					addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 2, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
					ch = inputCode(sv.maSv, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 20);
					on = false;
				}
				else
				{
					if (curRow >= 0 && curRow < 3)
					{
						normal();
						drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);	
						if (curRow == 1)	ch = inputStdName(sv.ho, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 44);
						if (curRow == 2)	ch = inputStdName(sv.ten, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 15);	
						if (curRow == 3)	ch = inputHandling1(sv.password, x + 4 + addStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 31, 31, isShowPassword);
						on = false;
					}
					else
					{
						if (curRow == 3)
						{
							normal();
							drawRectangle(x + 3 + addStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - addStudentMenu[5].length() - 2, 3);
							curRow++;
							ch = chooseSex(isMale);
							on = false;
						}
						else
						{
							if (curRow == 4)
							{
								if (isMale)		
								{
									sv.phai = "Nam";
									addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
									addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
								}
								else	
								{
									sv.phai = "Nu";	
									addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
									addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);					
								}
								curRow++;
								addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
							}
							else
							{
								if (curRow == 5 || curRow == 6)
								{
									addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow++;
									addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case ENTER:
				if (curRow < 4)
				{
					ch = DOWN;
					on = false;
				}
				if (curRow == 5)
				{
					if (checkStudentCode(sv, 0))
					{
						StudentNode *temp, *tail;
						for (tail = p; tail != NULL && tail->next != NULL; tail = tail->next);
						temp = new StudentNode;
						temp->data = sv;
						temp->next = NULL;
						if (p == NULL)
							p = temp;
						else
							tail->next = temp;
						tail = temp;
						Sleep(700);
						clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
						addStudent(p);
						return;
					}
				}
				if (curRow == 6)
				{
					if (isShowPassword)
					{
						gotoxy(x + 4 + addStudentMenu[5].length(), y + 2 + 3 * 3 + 1);
						setColor(FOREGROUND_LIGHTCYAN);
						cout << string(sv.password.length(), '*');
						isShowPassword = false;
						addStudentMenu[curRow + 1] = "Hien thi mat khau";
						addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 1, 38, 1, 0, BACKGROUND_LIGHTCYAN);
					}
					else
					{
						gotoxy(x + 4 + addStudentMenu[5].length(), y + 2 + 3 * 3 + 1);
						setColor(FOREGROUND_LIGHTCYAN);
						cout << sv.password;
						isShowPassword = true;
						addStudentMenu[curRow + 1] = "An mat khau";
						addButton(addStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 1, 38, 1, 0, BACKGROUND_LIGHTCYAN);
					}
				}
				if (curRow == 7)
				{
					clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
					return;
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
				return;
		}
	}
}
void printStudentList(StudentNode *p, int curRow, int index)
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;	
	clearTable2();
	if (p != NULL)
	{
		int start = index - curRow;
		int n = getNumberOfNode(p);
		StudentNode *temp = getNode(p, start);
		for (int i = start, j = 0; i < (n > 29 ? start + 29 : n); i++, j++)
		{
			infoBar3(x, y + j, temp, i);
			temp = temp->next;
		}
		lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
		infoBar3(x, y + curRow, getNode(p, index), index);
	}
}
void manipulateStudentList(Class &a, int mode) // mode == 0: chi xem, mode != 0: co the chinh sua
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;
	normal();
	table2(a.maLop, mode);
	int curRow = 0, index = 0;
	int n = getNumberOfNode(a.head);
	StudentNode *temp = a.head;
	printStudentList(temp, curRow, index);
	char ch;
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;		
		switch(ch)
		{
			case UP:
				if (a.head == NULL)	break;
				if (n > 29)
				{
					if (curRow - 1 == -1 && index == 0)
					{
						curRow = 28, index = n - 1;
						temp = getNode(a.head, index);
						printStudentList(a.head, curRow, index);
					}
					else
					{
						if (curRow - 1 == -1 && index != 0)
						{
							temp = getNode(a.head, --index);
							printStudentList(a.head, curRow, index);
						}
						else
						{
							if (curRow - 1 > -1)
							{
								lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);	
								infoBar3(x, y + curRow, temp, index);	
								curRow--, index--;
								temp = getNode(a.head, index);
								lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar3(x, y + curRow, temp, index);									
							}
						}
					}					
				}
				else
				{
					if (curRow - 1 == -1)
					{
						lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar3(x, y + curRow, temp, index);
						curRow = index = n - 1;
						temp = getNode(a.head, index);
						lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar3(x, y + curRow, temp, index);						
					}					
					else
					{
						if (curRow - 1 > -1)
						{
							lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar3(x, y + curRow, temp, index);
							curRow--, index--;
							temp = getNode(a.head, index);
							lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar3(x, y + curRow, temp, index);
						}						
					}
				}
				break;
			case DOWN:
				if (a.head == NULL)	break;
				if (n > 29)
				{
					if (curRow + 1 == 29 && index == n - 1)
					{
						curRow = index = 0;	
						temp = a.head;
						printStudentList(a.head, curRow, index);
					}			
					else
					{
						if (curRow + 1 == 29 && index != n - 1)
						{
							temp = temp->next;
							index++;
							printStudentList(a.head, curRow, index);
						}
						else
						{
							if (curRow + 1 < 29)
							{
								lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);
								infoBar3(x, y + curRow, temp, index);
								curRow++, index++;
								temp = temp->next;
								lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar3(x, y + curRow, temp, index);
							}							
						}
					}		
				}
				else
				{
					if (curRow + 1 == n)
					{
						lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar3(x, y + curRow, temp, index);
						curRow = index = 0;
						temp = a.head;
						lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar3(x, y + curRow, temp, index);						
					}
					else
					{
						if (curRow + 1 < n)
						{
							lightBar2(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar3(x, y + curRow, temp, index);
							curRow++, index++;
							temp = temp->next;
							lightBar2(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar3(x, y + curRow, temp, index);
						}
					}					
				}
				break;
			case DEL:
				if (mode != 0)
				{
					if (a.head == NULL)
					{
						notificationBlock("Danh sach trong, ban khong the xoa!", x + (horizontal - 46) / 2, y + (vertical - 5) / 2, 41, FOREGROUND_RED);
						printStudentList(a.head, curRow, index);
					}
					else
					{
						if (verifyingDeleteBlock(x + (horizontal - 46) / 2, y + (vertical - 5) / 2))
						{
							deleteStudent(a.head, index);
							saveStudentList(a);
							n = getNumberOfNode(a.head);
							curRow = index = 0;
							temp = a.head;
							printStudentList(a.head, curRow, index);
						}
						else
							printStudentList(a.head, curRow, index);
					}
				}
				break;
			case ENTER:
				if (mode != 0 && a.head != NULL)
				{
					clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
					string old = temp->data.maSv;
					adjustStudent(a.head, index);
					saveStudentList(a);
					for (int i = 0; i < b.n; i++)
						rename(("BAITHI_" + b.mh[i]->maMh + "_" + old + ".txt").c_str(), ("BAITHI_" + b.mh[i]->maMh + "_" + temp->data.maSv + ".txt").c_str());
					for (int i = 0; i < b.n; i++)
						saveScoreList(a, *b.mh[i]);
					normal();
					table2(a.maLop, mode);
					printStudentList(a.head, curRow, index);
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
				return;
		}
	}
}
int getNumberOfNode(StudentNode *p)
{
	int count = 0;
	for (StudentNode *temp = p; temp != NULL; temp = temp->next, count++);
	return count;
}
StudentNode *getNode(StudentNode *p, int index)
{
	StudentNode *temp = p;
	for (int i = 0; temp != NULL; temp = temp->next, i++)
		if (i == index)
			return temp;
	return NULL;
}
int getPositionOfNode(StudentNode *p, StudentNode *q) // q nut can lay vi tri
{
	int index = 0;
	for (StudentNode *temp = p; temp != NULL; temp = temp->next, index++)
	{
		if (temp == q)
			return index;
	}
	return -1;
}
void deleteStudent(StudentNode *&p, int index)
{
	StudentNode *temp, *temp1;
	if (index == 0) // xoa dau
	{
		temp = p; // luu vao bien tam de giai phong bo nho
		p = temp->next;
		delete temp;
	}
	else
	{
		temp = getNode(p, index - 1); // lay nut truoc nut can xoa
		temp1 = temp->next;
		temp->next = temp1->next;
		delete temp1;
	}
}
void adjustStudent(StudentNode *&p, int index)
{
	int x = 110, y = 7, horizontal = 70, vertical = 24;
	string adjustStudentMenu[9] = {"SUA DOI THONG TIN SINH VIEN",
									"MSSV: ",
									"Ho: ",
									"Ten: ",
									"Mat khau: ",
									"Gioi tinh: ",
									"Luu thay doi",
									"Hien thi mat khau",
									"Tro ve"};
	studentTable(adjustStudentMenu);
	StudentNode *temp = getNode(p, index);
	Student sv = temp->data;
	int curRow = 0;		
	bool isMale = true;
	if (sv.phai == "Nu")
	{
		addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
		addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);	
		isMale = false;	
	}
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
	gotoxy(x + 4 + adjustStudentMenu[5].length(), y + 6); cout << sv.ho;
	gotoxy(x + 4 + adjustStudentMenu[5].length(), y + 9); cout << sv.ten;
	gotoxy(x + 4 + adjustStudentMenu[5].length(), y + 12); cout << string(sv.password.length(), '*');
	bool on = false, isShowPassword = false;
	char ch = inputCode(sv.maSv, x + 4 + adjustStudentMenu[5].length(), y + 3, 20);
	while (true)
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
				if (curRow - 1 == -1)
				{
					normal();
					drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
					curRow = 7;
					addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 2, 38, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow > 0 && curRow < 4)
					{
						normal();
						drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
						if (curRow == 0)	ch = inputCode(sv.maSv, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 20);
						if (curRow == 1)	ch = inputStdName(sv.ho, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 44);
						if (curRow == 2)	ch = inputStdName(sv.ten, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 15);
						on = false;
					}
					else
					{
						if (curRow == 4)
						{
							if (isMale)		
							{
								sv.phai = "Nam";
								addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
								addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
							}
							else	
							{
								sv.phai = "Nu";	
								addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
								addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);					
							}
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
							ch = inputHandling1(sv.password, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 31, 31, isShowPassword);
							on = false;
						}
						else
						{
							if (curRow == 5)
							{
								addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 0, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								ch = chooseSex(isMale);
								on = false;
							}
							else
							{
								if (curRow == 6 || curRow == 7)
								{
									addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow--;
									addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case DOWN:
				if (curRow + 1 == 8)
				{
					addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 2, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
					ch = inputCode(sv.maSv, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 20);
					on = false;
				}
				else
				{
					if (curRow >= 0 && curRow < 3)
					{
						normal();
						drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);	
						if (curRow == 1)	ch = inputStdName(sv.ho, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 44);
						if (curRow == 2)	ch = inputStdName(sv.ten, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 15);	
						if (curRow == 3)	ch = inputHandling1(sv.password, x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow + 1, 31, 31, isShowPassword);
						on = false;
					}
					else
					{
						if (curRow == 3)
						{
							normal();
							drawRectangle(x + 3 + adjustStudentMenu[5].length(), y + 2 + 3 * curRow, horizontal - 3 - adjustStudentMenu[5].length() - 2, 3);
							curRow++;
							ch = chooseSex(isMale);
							on = false;
						}
						else
						{
							if (curRow == 4)
							{
								if (isMale)		
								{
									sv.phai = "Nam";
									addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);
									addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
								}
								else	
								{
									sv.phai = "Nu";	
									addButton("Nam", x + 16 + 5, y + 15, 9, 1, 0, BACKGROUND_BRIGHTWHITE);
									addButton("Nu", x + 16 + 5 + 19, y + 15, 9, 1, 0, BACKGROUND_LIGHTYELLOW);					
								}
								curRow++;
								addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
							}
							else
							{
								if (curRow == 5 || curRow == 6)
								{
									addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow++;
									addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * (curRow - 5), 38, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case ENTER:
				if (curRow < 4)
				{
					ch = DOWN;
					on = false;
				}
				if (curRow == 5)
				{
					string old = temp->data.maSv;
					temp->data.maSv = "";
					if (checkStudentCode(sv, 1))
					{
						temp->data = sv;
						Sleep(1000);
						clearPartOfScreen(x, y + vertical, horizontal, 3); // xoa khoi thong bao
					}
					else
						temp->data.maSv = old;
					
				}
				if (curRow == 6)
				{
					if (isShowPassword)
					{
						gotoxy(x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * 3 + 1);
						setColor(FOREGROUND_LIGHTCYAN);
						cout << string(sv.password.length(), '*');
						isShowPassword = false;
						adjustStudentMenu[curRow + 1] = "Hien thi mat khau";
						addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 1, 38, 1, 0, BACKGROUND_LIGHTCYAN);
					}
					else
					{
						gotoxy(x + 4 + adjustStudentMenu[5].length(), y + 2 + 3 * 3 + 1);
						setColor(FOREGROUND_LIGHTCYAN);
						cout << sv.password;
						isShowPassword = true;
						adjustStudentMenu[curRow + 1] = "An mat khau";
						addButton(adjustStudentMenu[curRow + 1], x + 16, y + 17 + 2 * 1, 38, 1, 0, BACKGROUND_LIGHTCYAN);
					}
				}
				if (curRow == 7)
				{
					clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
					return;
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
				return;				
		}
	}	
}
void saveStudentList(Class a)
{
	ofstream outFile(a.maLop + ".txt");
	outFile << getNumberOfNode(a.head) << endl;
	for (StudentNode *temp = a.head; temp != NULL; temp = temp->next)
	{
		outFile << temp->data.maSv << '/' << temp->data.ho << '/'
				<< temp->data.ten << '/' << temp->data.phai << '/'
				<< temp->data.password << endl;
	}
	outFile.close();
}
void loadStudentList(ClassList &a)
{
	for (int i = 0; i < a.n; i++)
	{
		ifstream inFile(a.lop[i].maLop + ".txt");
		if (inFile.fail())	continue;
		int slsv;
		inFile >> slsv;  // so luong sinh vien
		inFile.ignore();
		StudentNode *temp, *tail;
		while (slsv--)
		{
			temp = new StudentNode;
			getline(inFile, temp->data.maSv, '/');
			getline(inFile, temp->data.ho, '/');
			getline(inFile, temp->data.ten, '/');
			getline(inFile, temp->data.phai, '/');
			getline(inFile, temp->data.password);
			temp->next = NULL;		
			if (a.lop[i].head == NULL)
				a.lop[i].head = temp;
			else
				tail->next = temp;
			tail = temp;
		}
		inFile.close();
	}
}

