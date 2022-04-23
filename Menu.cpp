#include "Interface.h"
#include "Menu.h"
#include "Login.h"
#include "Class.h"
#include "Subject.h"
#include "Student.h"
#include "Question.h"
#include "MultipleChoiceTest.h"
#include "Score.h"
const int SIZE1 = 8;
const int SIZE2 = 2;
const int SIZE3 = 2;
const int SIZE4 = 2;

ClassList a;
SubjectList b;
extern QuestionNode *root;

string menu1[SIZE1] = {"LOP HOC",
				  	   "SINH VIEN",
					   "MON HOC",
					   "THEM CAU HOI THI",
					   "THI TRAC NGHIEM",
					   "IN BAI THI",
					   "IN BANG DIEM",
					   "DANG XUAT"};
string menu2[SIZE2] = {"THEM LOP HOC",
					   "DANH SACH LOP HOC"};
string menu3[SIZE3] = {"THEM SINH VIEN",
					   "DANH SACH SINH VIEN"};
string menu4[SIZE4] = {"THEM MON HOC",
				   	   "DANH SACH MON HOC"};		;
void manipulateMenu(string s[], int size, int x, int y, int horizontal, int vertical)
{
	int curRow = 0;
	addButton(s[0], x, y, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
	for (int i = 1; i < size; i++)
		addButton(s[i], x, y + 4 * i, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
	char ch;
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;
		switch(ch)
		{
			case UP: 
				if (curRow - 1 == -1)
				{
					addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
					curRow = size - 1;
					addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
				}
				else
					if (curRow - 1 > -1)
					{
						addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
						curRow--;
						addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
					}
				break;
			case DOWN:
				if (curRow + 1 == size)
				{
					addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
				}
				else	
					if (curRow + 1 < size)
					{
						addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
						curRow++;
						addButton(s[curRow], x, y + 4 * curRow, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
					}
				break;
			case ENTER:
				if (s == menu1)
				{
					if (curRow == 0)
						manipulateMenu(menu2, SIZE2, x + horizontal + 7, y + 4 * curRow, horizontal, vertical);
					if (curRow == 1)
						manipulateMenu(menu3, SIZE3, x + horizontal + 7, y + 4 * curRow, horizontal, vertical);
					if (curRow == 2)
						manipulateMenu(menu4, SIZE4, x + horizontal + 7, y + 4 * curRow, horizontal, vertical);
					if (curRow == 3)
					{
						int crRow = 0, index = 0;
						while (manipulateSubjectList(b, crRow, index, 0))
						{
							addQuestion(root, *b.mh[index]);
							saveQuestionList(root, *b.mh[index]);
						}
					}
					if (curRow == 4)
					{
						int soPhut = 0, soCauHoi = 0, crRow = 0, index = 0;
						while (manipulateSubjectList(b, crRow, index, 0))
						{
							if (input(root, *b.mh[index], soCauHoi, soPhut))
								multipleChoiceTest(*b.mh[index], root, soCauHoi, soPhut, 0);
							soPhut = soCauHoi = 0;
						}
					}
					if (curRow == 5)
					{
						int crRow = 0, index = 0;
						while (manipulateSubjectList(b, crRow, index, 0))
						{
							int crRow1 = 0, index1 = 0;
							while (manipulateClassList(a, crRow1, index1))
							{
								int crRow2 = 0, index2 = 0;
								while (manipulateScoreList(a.lop[index1], *b.mh[index], crRow2, index2, 1))
									reviewTest1(root, getNode(a.lop[index1].head, index2), a.lop[index1], *b.mh[index]);
							}
						}
					}
					if (curRow == 6)
					{
						int crRow = 0, index = 0;
						while (manipulateSubjectList(b, crRow, index, 0))
						{
							int crRow1 = 0, index1 = 0;
							while (manipulateClassList(a, crRow1, index1))
							{
								int crRow2 = 0, index2 = 0;
								manipulateScoreList(a.lop[index1], *b.mh[index], crRow2, index2, 0);
							}
						}
					}
					if (curRow == 7)
					{
						normal();
						system("cls");
						login();
						return;
					}	
				}
				if (s == menu2)
				{	
					if (curRow == 0)
					{
						addClass(a);
						saveClassList(a);
					}
					if (curRow == 1)
					{
						int crRow = 0, index = 0;
						while (manipulateClassList(a, crRow, index))
							manipulateStudentList(a.lop[index], 0);
					}
				}
				if (s == menu3)
				{
					int crRow = 0, index = 0;
					if (curRow == 0)
					{
						while (manipulateClassList(a, crRow, index))
						{
							addStudent(a.lop[index].head);
							saveStudentList(a.lop[index]);
						}
					}
					if (curRow == 1)
					{
						while (manipulateClassList(a, crRow, index))
							manipulateStudentList(a.lop[index], 1);
					}
				}
				if (s == menu4)
				{
					int crRow = 0, index = 0;
					if (curRow == 0)
					{
						addSubject(b);
						saveSubjectList(b);
					}
					if (curRow == 1)
						manipulateSubjectList(b, crRow, index, 1);
				}
				break;
			case ESC:
				if (s != menu1)
				{
					clearPartOfScreen(52, 2, horizontal, 31);
					return;
				}
				break;
		}
	}
}		 
void menu() // for teacher only
{
	system("cls"); 
	int x = 5, y = 2, horizontal = 40, vertical = 3;
	manipulateMenu(menu1, SIZE1, x, y, horizontal, vertical);
}
void studentView() // for student only
{
	system("cls");
	int x = 5, y = 2, horizontal = 40, vertical = 3;
	int curRow = 0;
	addButton("THI TRAC NGHIEM", x, y, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
	addButton("DANG XUAT", x, y + 4, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
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
				curRow++;
				addButton("THI TRAC NGHIEM", x, y, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
				addButton("DANG XUAT", x, y + 4, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
			}
			else
			{
				curRow--;
				addButton("THI TRAC NGHIEM", x, y, horizontal, vertical, 0, BACKGROUND_LIGHTCYAN);
				addButton("DANG XUAT", x, y + 4, horizontal, vertical, 0, BACKGROUND_BRIGHTWHITE);
			}
		}
		if (ch == ENTER)
		{
			if (curRow == 0)
			{
				int soPhut = 0, soCauHoi = 0, crRow = 0, index = 0;
				while (manipulateSubjectList(b, crRow, index, 0))
				{
					if (input(root, *b.mh[index], soCauHoi, soPhut))
						multipleChoiceTest(*b.mh[index], root, soCauHoi, soPhut, 1);
					soPhut = soCauHoi = 0;
				}
			}
			if (curRow == 1)
			{
				normal();
				system("cls");
				login();
				return;
			}
		}	
	}	
}

