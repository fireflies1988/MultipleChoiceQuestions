#include "Score.h"
#include "Interface.h"
#include "Student.h"
#include "MultipleChoiceTest.h"

// ScoreNode danh sach mon da thi cua Student
extern QuestionNode *root;
void updateScore(Subject a, ScoreNode *&head, double grade)
{
	ScoreNode *temp, *tail;
	for (tail = head; tail != NULL; tail = tail->next)
	{
		if (tail->data.maMh == a.maMh)
		{
			tail->data.diem = grade;
			return;
		}
	}
	for (tail = head; tail != NULL && tail->next != NULL; tail = tail->next);
	temp = new ScoreNode;
	temp->data.maMh = a.maMh;
	temp->data.diem = grade;
	temp->next = NULL;
	if (head == NULL)	head = temp;
	else	tail->next = temp;
	tail = temp;
}
void printScoreList(StudentNode *p, int curRow, int index, Subject a) // theo mon hoc
{
	int x = 100, y = 7, horizontal = 102, vertical = 33;
	clearTable3();
	if (p != NULL)
	{
		int start = index - curRow;
		int n = getNumberOfNode(p);
		StudentNode *temp = getNode(p, start);
		for (int i = start, j = 0; i < (n > 29 ? start + 29 : n); i++, j++)
		{
			infoBar3(x, y + j, temp, i, a);
			temp = temp->next;
		}
		lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
		infoBar3(x, y + curRow, getNode(p, index), index, a);
	}
}
bool manipulateScoreList(Class a, Subject b, int &curRow, int &index, int mode)
{
	int x = 100, y = 7, horizontal = 102, vertical = 33;
	normal();
	table3(b, a);
	int n = getNumberOfNode(a.head);
	StudentNode *temp = getNode(a.head, index);
	printScoreList(a.head, curRow, index, b);
	char ch;
	while (1)
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
					if (curRow == 0 && index == 0)
					{
						curRow = 28, index = n - 1;
						temp = getNode(a.head, index);
						printScoreList(a.head, curRow, index, b);
					}
					else
					{
						if (curRow == 0 && index != 0)
						{
							temp = getNode(a.head, --index);
							printScoreList(a.head, curRow, index, b);
						}
						else
						{
							if (curRow > 0)
							{
								lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
								infoBar3(x, y + curRow, temp, index, b);
								curRow--, index--;
								temp = getNode(a.head, index);
								lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar3(x, y + curRow, temp, index, b);
							}
						}
					}
				}
				else
				{
					if (curRow == 0)
					{
						lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar3(x, y + curRow, temp, index, b);
						curRow = index = n - 1;
						temp = getNode(a.head, index);
						lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar3(x, y + curRow, temp, index, b);
					}
					else
					{
						if (curRow > 0)
						{
							lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar3(x, y + curRow, temp, index, b);
							curRow--, index--;
							temp = getNode(a.head, index);
							lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar3(x, y + curRow, temp, index, b);
						}
					}
				}
				break;
			case DOWN:
				if (a.head == NULL)		break;	
				if (n > 29)
				{
					if (curRow == 28 && index == n - 1)
					{
						curRow = index = 0;
						temp = a.head;
						printScoreList(a.head, curRow, index, b);
					}
					else
					{
						if (curRow == 28 && index != n - 1)
						{
							temp = temp->next;
							index++;
							printScoreList(a.head, curRow, index, b);
						}
						else
						{
							if (curRow < 28)
							{
								lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
								infoBar3(x, y + curRow, temp, index, b);
								curRow++, index++;
								temp = temp->next;
								lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
								infoBar3(x, y + curRow, temp, index, b);
							}
						}
					}
				}
				else
				{
					if (curRow == n - 1)
					{
						lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
						infoBar3(x, y + curRow, temp, index, b);
						curRow = index = 0;
						temp = a.head;
						lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
						infoBar3(x, y + curRow, temp, index, b);
					}
					else
					{
						if (curRow < n - 1)
						{
							lightBar3(x, y + curRow, horizontal, FOREGROUND_WHITE);
							infoBar3(x, y + curRow, temp, index, b);
							curRow++, index++;
							temp = temp->next;
							lightBar3(x, y + curRow, horizontal, BACKGROUND_LIGHTCYAN);
							infoBar3(x, y + curRow, temp, index, b);
						}
					}
				}
				break;
			case ENTER:
				if (mode != 0 && a.head != NULL)
				{
					for (ScoreNode *temp1 = temp->data.head; temp1 != NULL; temp1 = temp1->next)
					{
						if (temp1->data.maMh == b.maMh)
						{
							clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
							return true;
						}
					}
					notificationBlock("Sinh vien nay chua thi, ban khong the xem bai", x + (horizontal - 50) / 2, y + (vertical - 5) / 2, 50, FOREGROUND_RED);
					printScoreList(a.head, curRow, index, b);
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 3, horizontal, vertical + 7);
				return false;
		}		
	}
}
int getNumberOfStudentTested(Class a, Subject b)  // so sinh lop a da duoc thi mon b
{
	int count = 0;
	for (StudentNode *temp = a.head; temp != NULL; temp = temp->next)
	{
		for (ScoreNode *temp1 = temp->data.head; temp1 != NULL; temp1 = temp1->next)
		{
			if (temp1->data.maMh == b.maMh)
			{
				count++;
				break;
			}
		}
	}
	return count;
}
void clearScoreList(ScoreNode *&p)
{
	ScoreNode *temp;
	for (; temp != NULL; delete temp)
	{
		temp = p;
		p = p->next;
	}
}
void saveScoreList(Class a, Subject b)
{
	ofstream outFile("DIEMTHI_" + b.maMh + "_" + a.maLop + ".txt");
	outFile << getNumberOfStudentTested(a, b) << endl;
	for (StudentNode *temp = a.head; temp != NULL; temp = temp->next)
	{
		for (ScoreNode *temp1 = temp->data.head; temp1 != NULL; temp1 = temp1->next)
		{
			if (temp1->data.maMh == b.maMh)
			{
				outFile << temp->data.maSv << '/' << temp1->data.diem << endl;
				break;
			}
		}
	}
	outFile.close();
}
void loadScoreList(ClassList &a, SubjectList b)
{
	for (int i = 0; i < a.n; i++)
	{
		for (int j = 0; j < b.n; j++)
		{
			ifstream inFile("DIEMTHI_" + b.mh[j]->maMh + "_" + a.lop[i].maLop + ".txt");
			if (inFile.fail())	continue;
			int numberOfStudentTested;
			inFile >> numberOfStudentTested;
			inFile.ignore();
			ScoreNode *temp, *tail;
			while (numberOfStudentTested--)
			{
				string maSv;
				temp = new ScoreNode;
				getline(inFile, maSv, '/');
				inFile >> temp->data.diem;
				inFile.ignore();
				temp->data.maMh = b.mh[j]->maMh;
				temp->next = NULL;
				for (StudentNode *temp1 = a.lop[i].head; temp1 != NULL; temp1 = temp1->next)
				{
					if (temp1->data.maSv == maSv)
					{
						for (tail = temp1->data.head; tail != NULL && tail->next != NULL; tail = tail->next);
						if (temp1->data.head == NULL)
							temp1->data.head = temp;
						else
							tail->next = temp;
						tail = temp;
						break;
					}
				}
			}
			inFile.close();
		}
	}
}
