#include "Class.h"
#include "Interface.h"
#include "InputHandling.h"
#include "Student.h"

// maLop: bound = 29
// tenLop: overflowIndex = 53, bound = 58
bool checkClassCode(ClassList a, Class b)
{
	int x = 110, y = 21, horizontal = 70, vertical = 3;
	for (int i = 0; i < a.n; i++)
	{
		if (b.maLop == a.lop[i].maLop)
		{
			notification("Ma lop da ton tai. Moi ban nhap lai!", x, y, horizontal, vertical, FOREGROUND_RED);
			return false;
		}
	}
	if (b.maLop == "" || b.tenLop == "")
	{
		notification("Ma lop va ten lop khong duoc bo trong!", x, y, horizontal, vertical, FOREGROUND_RED);
		return false;
	}
	else
	{
		notification("Them lop thanh cong!", x, y, horizontal, vertical, FOREGROUND_LIGHTGREEN);
		return true;
	}
}
void classTable(string menu[5])
{
	int x = 110, y = 7, horizontal = 70, vertical = 14;
	normal();
	alignCenter(menu[0], x, y - 1, horizontal); // tieu de
	drawRectangle(x, y, horizontal, vertical); // khung vien ngoai
	// ma lop
	gotoxy(x + 3, y + 3); cout << menu[1];
	drawRectangle(x + 3 + menu[2].length(), y + 2, horizontal - 3 - menu[2].length() - 2, 3);
	// ten lop
	gotoxy(x + 3, y + 6); cout << menu[2];
	drawRectangle(x + 3 + menu[2].length(), y + 5, horizontal - 3 - menu[2].length() - 2, 3);
	// them lop, tro ve
	addButton(menu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE); // 70 - 2 * 16
	addButton(menu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
}
void addClass(ClassList &a)
{
	int x = 110, y = 7, horizontal = 70, vertical = 14;
	string addClassMenu[5] = {"THEM LOP HOC",
						   	  "Ma lop: ",
						   	  "Ten lop: ",
						      "Them lop",
						      "Tro ve"};
	classTable(addClassMenu);		
	int curRow = 0;
	Class b;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + addClassMenu[2].length(), y + 2, horizontal - 3 - addClassMenu[2].length() - 2, 3);
	char ch = inputCode(b.maLop, x + 4 + addClassMenu[2].length(), y + 3, 29);
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
					drawRectangle(x + 3 + addClassMenu[2].length(), y + 2, horizontal - 3 - addClassMenu[2].length() - 2, 3);
					curRow = 3;
					addButton(addClassMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow - 1 == 0)
					{
						normal();
						drawRectangle(x + 3 + addClassMenu[2].length(), y + 5, horizontal - 3 - addClassMenu[2].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addClassMenu[2].length(), y + 2, horizontal - 3 - addClassMenu[2].length() - 2, 3);
						ch = inputCode(b.maLop, x + 4 + addClassMenu[2].length(), y + 3, 29);
						on = false;
					}
					else
					{
						if (curRow - 1 == 1)
						{
							addButton(addClassMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + addClassMenu[2].length(), y + 5, horizontal - 3 - addClassMenu[2].length() - 2, 3);
							ch = inputStandard(b.tenLop, x + 4 + addClassMenu[2].length(), y + 6, 53, 58);
							on = false;
						}
						else
						{
							if (curRow - 1 == 2)
							{
								addButton(addClassMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								addButton(addClassMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
							}
						}
					}
				}
				break;
			case DOWN:
				if (curRow + 1 == 4)
				{
					addButton(addClassMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + addClassMenu[2].length(), y + 2, horizontal - 3 - addClassMenu[2].length() - 2, 3);
					ch = inputCode(b.maLop, x + 4 + addClassMenu[2].length(), y + 3, 29);
					on = false;
				}
				else
				{
					if (curRow + 1 == 1)
					{
						normal();
						drawRectangle(x + 3 + addClassMenu[2].length(), y + 2, horizontal - 3 - addClassMenu[2].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addClassMenu[2].length(), y + 5, horizontal - 3 - addClassMenu[2].length() - 2, 3);
						ch = inputStandard(b.tenLop, x + 4 + addClassMenu[2].length(), y + 6, 53, 58);
						on = false;
					}
					else
					{
						if (curRow + 1 == 2)
						{
							normal();
							drawRectangle(x + 3 + addClassMenu[2].length(), y + 5, horizontal - 3 - addClassMenu[2].length() - 2, 3);
							curRow++;
							addButton(addClassMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_LIGHTCYAN);
						}
						else
						{
							if (curRow + 1 == 3)
							{
								addButton(addClassMenu[3], x + 16, y + 9, 38, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow++;
								addButton(addClassMenu[4], x + 16, y + 11, 38, 1, 0, BACKGROUND_LIGHTCYAN);
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
					if (checkClassCode(a, b))
					{
						a.lop[a.n++] = b;
						Sleep(700);
						clearPartOfScreen(x, y - 2, horizontal, vertical + 5);
						addClass(a);
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
void printClassList(ClassList a, int curRow, int index)
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;
	clearTable1(x, y, horizontal, vertical);
	if (a.n != 0)
	{
		int start = index - curRow;  // chi so bat dau de in
		for (int i = start, j = 0; i < (a.n > 29 ? start + 29 : a.n); i++, j++)
			infoBar1(x, y + j, horizontal, a, i);
		lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
		infoBar1(x, y + curRow, horizontal, a, index);
	}
}
bool manipulateClassList(ClassList &a, int &curRow, int &index) // true: enter, false: exit
{
	int x = 100, y = 7, horizontal = 98, vertical = 33;
	string classMenu[4] = {"DANH SACH LOP HOC",
						   "STT",
						   "MA LOP",
						   "TEN LOP"};
	normal();
	table1(x, y, horizontal, vertical, classMenu, 0);
	printClassList(a, curRow, index);
	char ch;
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;
		switch(ch)
		{
			case UP:
				if (a.n == 0)	break;
				if (a.n > 29)
				{
					if (curRow - 1 == -1 && index == 0)
					{
						curRow = 28, index = a.n - 1;
						printClassList(a, curRow, index);
					}
					else
					{
						if (curRow - 1 == -1 && index != 0)
							printClassList(a, curRow, --index);
						else
						{
							if (curRow - 1 > -1)
							{
								lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);	
								infoBar1(x, y + curRow, horizontal, a, index);	
								curRow--, index--;
								lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar1(x, y + curRow, horizontal, a, index);					
							}
						}
					}
				}
				else
				{
					if (curRow - 1 == -1)
					{
						lightBar1(x, y, horizontal, FOREGROUND_WHITE);
						infoBar1(x, y, horizontal, a, index);
						curRow = index = a.n - 1;
						lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar1(x, y + curRow, horizontal, a, index);
					}
					else
					{
						if (curRow - 1 > -1)
						{
							lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar1(x, y + curRow, horizontal, a, index);
							curRow--, index--;
							lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar1(x, y + curRow, horizontal, a, index);
						}
					}
				}
				break;
			case DOWN:	
				if (a.n == 0) break;
				if (a.n > 29)
				{
					if (curRow + 1 == 29 && index == a.n - 1)
					{
						curRow = index = 0;	
						printClassList(a, curRow, index);
					}
					else
					{
						if (curRow + 1 == 29 && index != a.n - 1)
							printClassList(a, curRow, ++index);
						else
						{
							if (curRow + 1 < 29)
							{
								lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
								infoBar1(x, y + curRow, horizontal, a, index);
								curRow++, index++;
								lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar1(x, y + curRow, horizontal, a, index);
							}
						}
					}
				}
				else
				{
					
					if (curRow + 1 == a.n)
					{
						lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar1(x, y + curRow, horizontal, a, index);
						curRow = index = 0;
						lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar1(x, y + curRow, horizontal, a, index);						
					}
					else
					{
						if (curRow + 1 < a.n)
						{
							lightBar1(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar1(x, y + curRow, horizontal, a, index);
							curRow++, index++;
							lightBar1(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar1(x, y + curRow, horizontal, a, index);
						}
					}
				}
				break;
			case ENTER:
				clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
				return true;
			case ESC:
				clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
				return false;
		}		
	}
}
void saveClassList(ClassList a)
{
	ofstream outFile("DSLH.txt");
	outFile << a.n << endl;
	for (int i = 0; i < a.n; i++)
		outFile << a.lop[i].maLop << '/' << a.lop[i].tenLop << endl;
	outFile.close();
}
void loadClassList(ClassList &a)
{
	ifstream inFile("DSLH.txt");
	inFile >> a.n;
	inFile.ignore(); // bo qua endl
	for (int i = 0; i < a.n; i++)
	{
		getline(inFile, a.lop[i].maLop, '/');
		getline(inFile, a.lop[i].tenLop);
	}
	inFile.close();
}
void deleteClass(ClassList &a)  //* chon lop de xoa
{
	string maLop;
	cout << "Nhap ma lop ban muon xoa: "; cin >> maLop; //* thiet lap nut chon lop de xoa
	for (int i = 0; i < a.n; i++)
	{
		if (maLop == a.lop[i].maLop)
		{
			for (int j = i; j < a.n - 1; j++)
				a.lop[j] = a.lop[j + 1];
			a.n--;
			cout << "Xoa lop thanh cong!" << endl; //* hieu chinh mau xanh...
			break;
		}
		if (i == a.n - 1)	cout << "Lop nay khong ton tai!" << endl;  //*
	}
}
void adjustClass(ClassList &a)
{
	string maLop;
	Class b;
	cout << "Nhap ma lop ban muon hieu chinh: "; cin >> maLop;
	for (int i = 0; i < a.n; i++)
	{
		if (a.lop[i].maLop == maLop)
		{
			a.lop[i].maLop = "";
//			inputClass(a, b);
//			strcpy(a.lop[i].maLop, b.maLop);
//			strcpy(a.lop[i].tenLop, b.tenLop);
			break;
		}
	}
}
