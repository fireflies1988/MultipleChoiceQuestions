#include "Subject.h"
#include "Interface.h"
#include "InputHandling.h"
#include "Question.h"
#include "Score.h"

// maMh: bound = 29
// tenMh: overflowIndex = 49, bound = 58
extern QuestionNode *root;
extern ClassList a;
bool checkSubjectCode(SubjectList a, Subject b, int mode) // mode == 0: Them mon hoc thanh cong!, mode != 1: Luu thay doi thanh cong!
{
	int x = 110, y = 21, horizontal = 70, vertical = 3;	
	for (int i = 0; i < a.n; i++)
	{
		if (b.maMh == a.mh[i]->maMh)
		{
			notification("Ma mon hoc da ton tai. Moi ban nhap lai!", x, y, horizontal, vertical, FOREGROUND_RED);
			return false;
		}
	}
	if (b.maMh == "" || b.tenMh == "")
	{
		notification("Ma mon hoc va ten mon hoc khong duoc bo trong!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	else
	{
		notification(mode == 0 ? "Them mon hoc thanh cong!" : "Luu thay doi thanh cong!", x, y, horizontal, vertical, FOREGROUND_LIGHTGREEN);
		return true;
	}
}
void subjectTable(string menu[5])
{
	int x = 110, y = 7, horizontal = 70, vertical = 14;
	normal();
	alignCenter(menu[0], x, y - 1, horizontal);  // tieu de
	drawRectangle(x, y, horizontal, vertical);	// khung vien
	// ma mon hoc
	gotoxy(x + 3, y + 3); cout << menu[1];
	drawRectangle(x + 3 + menu[2].length(), y + 2, horizontal - 3 - menu[2].length() - 2, 3);
	// ten mon hoc
	gotoxy(x + 3, y + 6); cout << menu[2];
	drawRectangle(x + 3 + menu[2].length(), y + 5, horizontal - 3 - menu[2].length() - 2, 3);
	// them mon hoc/luu thay doi, tro ve
	addButton(menu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE); // 70 - 2 * 16
	addButton(menu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE); // horizontal - 2 * 16
}
void addSubject(SubjectList &a)
{
	int x = 110, y = 7, horizontal = 70, vertical = 14;
	Subject b;
	string addSubjectMenu[5] = {"THEM MON HOC",
								"Ma mon hoc: ",
								"Ten mon hoc: ",
								"Them mon hoc",
								"Tro ve"};
	subjectTable(addSubjectMenu);
	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 2, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
	char ch = inputCode(b.maMh, x + 4 + addSubjectMenu[2].length(), y + 3, 29);
	bool on = false;	
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
					drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 2, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
					curRow = 3;
					addButton(addSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow - 1 == 0)
					{
						normal();
						drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 5, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 2, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
						ch = inputCode(b.maMh, x + 4 + addSubjectMenu[2].length(), y + 3, 29);
						on = false;
					}	
					else
					{
						if (curRow - 1 == 1)
						{
							addButton(addSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 5, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
							ch = inputStandard(b.tenMh, x + 4 + addSubjectMenu[2].length(), y + 6, 49, 58);
							on = false;
						}	
						else
						{
							if (curRow - 1 == 2)
							{
								addButton(addSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								addButton(addSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
							}						
						}					
					}				
				}
				break;
			case DOWN:
				if (curRow + 1 == 4)
				{
					addButton(addSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 2, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
					ch = inputCode(b.maMh, x + 4 + addSubjectMenu[2].length(), y + 3, 29);
					on = false;
				}
				else
				{
					if (curRow + 1 == 1)
					{
						normal();
						drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 2, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 5, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
						ch = inputStandard(b.tenMh, x + 4 + addSubjectMenu[2].length(), y + 6, 49, 58);
						on = false;
					}		
					else
					{
						if (curRow + 1 == 2)
						{
							normal();
							drawRectangle(x + 3 + addSubjectMenu[2].length(), y + 5, horizontal - 3 - addSubjectMenu[2].length() - 2, 3);
							curRow++;
							addButton(addSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
						}	
						else
						{		
							if (curRow + 1 == 3)
							{
								addButton(addSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow++;
								addButton(addSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
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
				if (curRow == 2)
				{
					if (checkSubjectCode(a, b, 0))
					{
						a.mh[a.n] = new Subject;
						*a.mh[a.n++] = b;
						Sleep(700);
						clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
						addSubject(a);
						return;
					}
				}
				if (curRow == 3)
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
void deleteSubject(SubjectList &a, int index) 
{
	delete a.mh[index];  //???
	for (int i = index; i < a.n - 1; i++)
		a.mh[i] = a.mh[i + 1];  
	a.n--;
}
void adjustSubject(SubjectList &a, int index) // index chi so phan tu
{
	int x = 110, y = 7, horizontal = 70, vertical = 14;
	string adjustSubjectMenu[5] = {"HIEU CHINH MON HOC",
								   "Ma mon hoc: ",
								   "Ten mon hoc: ",
								   "Luu thay doi",
								   "Tro ve"};
	subjectTable(adjustSubjectMenu);
	Subject b = *a.mh[index];   
	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 2, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
	gotoxy(x + 4 + adjustSubjectMenu[2].length(), y + 6);  
	if (b.tenMh.length() > 49)
	{
		string temp = b.tenMh;
		for (int i = temp.length() - 49; i < temp.length(); i++)
			cout << temp[i];
	}
	else	cout << b.tenMh;
	char ch = inputCode(b.maMh, x + 4 + adjustSubjectMenu[2].length(), y + 3, 29);
	bool on = false;	
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
					drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 2, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
					curRow = 3;
					addButton(adjustSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow - 1 == 0)
					{
						normal();
						drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 5, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 2, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
						ch = inputCode(b.maMh, x + 4 + adjustSubjectMenu[2].length(), y + 3, 29);
						on = false;
					}	
					else
					{
						if (curRow - 1 == 1)
						{
							addButton(adjustSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 5, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
							ch = inputStandard(b.tenMh, x + 4 + adjustSubjectMenu[2].length(), y + 6, 49, 58);
							on = false;
						}	
						else
						{
							if (curRow - 1 == 2)
							{
								addButton(adjustSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								addButton(adjustSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
							}						
						}					
					}				
				}
				break;
			case DOWN:
				if (curRow + 1 == 4)
				{
					addButton(adjustSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 2, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
					ch = inputCode(b.maMh, x + 4 + adjustSubjectMenu[2].length(), y + 3, 29);
					on = false;
				}
				else
				{
					if (curRow + 1 == 1)
					{
						normal();
						drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 2, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 5, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
						ch = inputStandard(b.tenMh, x + 4 + adjustSubjectMenu[2].length(), y + 6, 49, 58);
						on = false;
					}		
					else
					{
						if (curRow + 1 == 2)
						{
							normal();
							drawRectangle(x + 3 + adjustSubjectMenu[2].length(), y + 5, horizontal - 3 - adjustSubjectMenu[2].length() - 2, 3);
							curRow++;
							addButton(adjustSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
						}	
						else
						{		
							if (curRow + 1 == 3)
							{
								addButton(adjustSubjectMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow++;
								addButton(adjustSubjectMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
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
				if (curRow == 2)
				{
					string old = a.mh[index]->maMh;
					a.mh[index]->maMh = "";
					if (checkSubjectCode(a, b, 1))
					{
						*a.mh[index] = b;
						Sleep(1000);
						clearPartOfScreen(110, 21, 70, 3); // xoa khoi thong bao
					}	
					else	a.mh[index]->maMh = old;
				}
				if (curRow == 3)
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
void printSubjectList(SubjectList a, int curRow, int index)
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;
	clearTable1(x, y, horizontal, vertical);
	if (a.n != 0)
	{
		int start = index - curRow;  // chi so bat dau de in
		for (int i = start, j = 0; i < (a.n > 29 ? start + 29 : a.n); i++, j++)
			infoBar2(x, y + j, horizontal, a, i);
		lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
		infoBar2(x, y + curRow, horizontal, a, index);
	}
}
bool manipulateSubjectList(SubjectList &b, int &curRow, int &index, int mode)
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;
	string subjectMenu[4] = {"DANH SACH MON HOC",
							 "STT",
							 "MA MON HOC",
							 "TEN MON HOC"};
	normal();
	table1(x, y, horizontal, vertical, subjectMenu, mode);
	printSubjectList(b, curRow, index);
	char ch;
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;
		switch(ch)
		{
			case UP:
				if (b.n == 0)	break;
				if (b.n > 29)
				{
					if (curRow - 1 == -1 && index == 0)
					{
						curRow = 28, index = b.n - 1;
						printSubjectList(b, curRow, index);
					}
					else
					{
						if (curRow - 1 == -1 && index != 0)
							printSubjectList(b, curRow, --index);
						else
						{
							if (curRow - 1 > -1)
							{
								lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);	
								infoBar2(x, y + curRow, horizontal, b, index);	
								curRow--, index--;
								lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar2(x, y + curRow, horizontal, b, index);					
							}
						}
					}
				}
				else
				{
					if (curRow - 1 == -1)
					{
						lightBar1(x, y, horizontal, FOREGROUND_WHITE);
						infoBar2(x, y, horizontal, b, index);
						curRow = index = b.n - 1;
						lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar2(x, y + curRow, horizontal, b, index);
					}
					else
					{
						if (curRow - 1 > -1)
						{
							lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar2(x, y + curRow, horizontal, b, index);
							curRow--, index--;
							lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar2(x, y + curRow, horizontal, b, index);
						}
					}
				}
				break;
			case DOWN:	
				if (b.n == 0) break;
				if (b.n > 29)
				{
					if (curRow + 1 == 29 && index == b.n - 1)
					{
						curRow = index = 0;	
						printSubjectList(b, curRow, index);
					}
					else
					{
						if (curRow + 1 == 29 && index != b.n - 1)
							printSubjectList(b, curRow, ++index);
						else
						{
							if (curRow + 1 < 29)
							{
								lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
								infoBar2(x, y + curRow, horizontal, b, index);
								curRow++, index++;
								lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar2(x, y + curRow, horizontal, b, index);
							}
						}
					}
				}
				else
				{
					if (curRow + 1 == b.n)
					{
						lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar2(x, y + curRow, horizontal, b, index);
						curRow = index = 0;
						lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar2(x, y + curRow, horizontal, b, index);						
					}
					else
					{
						if (curRow + 1 < b.n)
						{
							lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar2(x, y + curRow, horizontal, b, index);
							curRow++, index++;
							lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar2(x, y + curRow, horizontal, b, index);
						}
					}
				}
				break;
			case DEL:
				if (mode != 0)
				{
					if (b.n == 0)
					{
						notificationBlock("Danh sach trong, ban khong the xoa!", x + (horizontal - 46) / 2, y + (vertical - 5) / 2, 41, FOREGROUND_RED);
						printSubjectList(b, curRow, index);
					}
					else
					{
						if (verifyingDeleteBlock(x + (horizontal - 46) / 2, y + (vertical - 5) / 2))
						{
							remove(("DSCH_" + b.mh[index]->tenMh + ".txt").c_str()); // xoa file dsch cua mon hoc nay
							deleteSubject(b, index);
							saveSubjectList(b);
							curRow = index = 0;
							printSubjectList(b, curRow, index);
						}
						else
							printSubjectList(b, curRow, index);
					}
				}
				break;
			case ENTER:
				if (b.n != 0 && mode != 0)
				{
					clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
					string temp = b.mh[index]->tenMh;
					string temp2 = b.mh[index]->maMh;
					adjustSubject(b, index);
					saveSubjectList(b);
					rename(("DSCH_" + temp + ".txt").c_str(), ("DSCH_" + b.mh[index]->tenMh + ".txt").c_str());
					for (int i = 0; i < a.n; i++)
						for (StudentNode *temp1 = a.lop[i].head; temp1 != NULL; temp1 = temp1->next)
							rename(("BAITHI_" + temp2 + "_" + temp1->data.maSv + ".txt").c_str(), ("BAITHI_" + b.mh[index]->maMh + "_" + temp1->data.maSv + ".txt").c_str());
					for (int i = 0; i < a.n; i++)
					{
						rename(("DIEMTHI_" + temp2 + "_" + a.lop[i].maLop + ".txt").c_str(), ("DIEMTHI_" + b.mh[index]->maMh + "_" + a.lop[i].maLop + ".txt").c_str());
						for (StudentNode *temp1 = a.lop[i].head; temp1 != NULL; temp1 = temp1->next)
							temp1->data.head = NULL;  // leaks memory
					}
					loadScoreList(a, b);
					root = NULL;  // leaks memory
					loadQuestionList(root, b);
					normal();
					table1(x, y, horizontal, vertical, subjectMenu, mode);
					printSubjectList(b, curRow, index);
				}
				if (mode == 0)	
				{
					clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
					return true;
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
				return false;
		}
	}
}
void saveSubjectList(SubjectList a)
{
	ofstream outFile("DSMH.txt");
	outFile << a.n << endl;
	for (int i = 0; i < a.n; i++)
		outFile << a.mh[i]->maMh << '/' << a.mh[i]->tenMh << endl;
	outFile.close();
}
void loadSubjectList(SubjectList &a)
{
	ifstream inFile("DSMH.txt");
	inFile >> a.n;
	inFile.ignore(); // bo qua endl
	for (int i = 0; i < a.n; i++)
	{
		a.mh[i] = new Subject;
		getline(inFile, a.mh[i]->maMh, '/');
		getline(inFile, a.mh[i]->tenMh);
	}
	inFile.close();
}
