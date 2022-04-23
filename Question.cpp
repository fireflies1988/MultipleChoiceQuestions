#include "Question.h"
#include "Interface.h"
#include "InputHandling.h"

extern Stack idStack;  // luu id cau hoi cua tat ca mon hoc

int push(Stack &st, int a)
{
	if (st.n == MAX_STACK_SIZE)		return 0;
	st.node[st.n++] = a;
	return 1;
}
int pop(Stack &st, int &a)
{
	if (st.n == 0)		return 0;
	a = st.node[--st.n];
	return 1;	
}
int max(int a, int b)
{
	return a > b ? a : b;
}
int height(QuestionNode *p)
{
	return p == NULL ? 0 : p->height;
}
// 		   z                                      y 
//        / \                                   /   \
//       y   T4      Right Rotate (z)          x      z
//      / \          - - - - - - - - ->      /  \    /  \ 
//     x   T3                               T1  T2  T3  T4
//    / \
//  T1   T2
QuestionNode *rightRotate(QuestionNode *z)
{
	QuestionNode *y = z->left;
	// Perform rotation
	z->left = y->right;
	y->right = z;
	// Update heights
	z->height = max(height(z->left), height(z->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}
//  z                                y 
// /  \                            /   \ 
//T1   y     Left Rotate(z)       z     x
//    / \   - - - - - - - ->    / \   / \
//   T2  x                    T1  T2 T3  T4
//      / \
//    T3  T4
QuestionNode *leftRotate(QuestionNode *z)
{
	QuestionNode *y = z->right;
	// Perform rotation
	z->right = y->left;
	y->left = z;
	// Update heights
	z->height = max(height(z->left), height(z->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;  // y tro thanh nut cha moi
}
int getBalance(QuestionNode *p)
{
	return p == NULL ? 0 : height(p->left) - height(p->right);
}
void questionTable(string menu[9])
{
	int x = 102, y = 7, horizontal = 98, vertical = 25;
	normal();
	alignCenter(menu[0], x, y - 1, horizontal);  // tieu de
	drawRectangle(x, y, horizontal, vertical);	// khung vien	
	// Noi dung, A, B, C, D
	for (int i = 1; i < 6; i++)
	{
		gotoxy(x + 3, y + 3 * i); cout << menu[i];
		drawRectangle(x + 3 + menu[1].length(), y - 1 + 3 * i, horizontal - 3 - menu[1].length() - 2, 3);
	}
	// Dap an, A, B, C, D
	gotoxy(x + 3, y + 18); cout << menu[6];
	string answer[4] = {"A", "B", "C", "D"};
	for (int i = 0; i < 4; i++)
		addButton(answer[i], x + 3 + menu[1].length() + 5 + 19 * i, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
	addButton(answer[0], x + 3 + menu[1].length() + 5, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
	// Them cau hoi, tro ve
	addButton(menu[7], x + 26, y + 20, 46, 1, 0, BACKGROUND_BRIGHTWHITE);
	addButton(menu[8], x + 26, y + 22, 46, 1, 0, BACKGROUND_BRIGHTWHITE);
}
char chooseAnswer(char &answer)
{
	int x = 102, y = 7, horizontal = 98, vertical = 25;
	int curCol = 0, picked;
	char ch;
	string a[4] = {"A", "B", "C", "D"};
	for (picked = 0; picked < 4 && answer != 'A' + picked; picked++); // tim dap an duoc chon
	addButton(a[0], x + 13 + 5, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
	while (true)
	{
		if ((ch = getch()) == -32)	ch = getch();
		else
			if (ch != ENTER && ch != ESC) 	continue;	
		switch(ch)
		{
			case LEFT:
				if (curCol == 0)
				{
					addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
					addButton(a[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
					curCol = 3;
					addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{	
					if (curCol > 0)
					{
						addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
						addButton(a[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
						curCol--;
						addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
					}
				}
				break;
			case RIGHT:
				if (curCol == 3)
				{
					addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
					addButton(a[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
					curCol = 0;
					addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curCol < 3)
					{
						addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
						addButton(a[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
						curCol++;
						addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
					}
				}
				break;
			case ENTER:
				picked = curCol;
				for (int i = 0; i < 4; i++)
					addButton(a[i], x + 13 + 5 + 19 * i, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
				addButton(a[curCol], x + 13 + 5 + 19 * curCol, y + 18, 11, 1, 0, BACKGROUND_LIGHTCYAN);
				answer = 'A' + picked;
				break;
			case UP:
			case DOWN:
			case ESC:
				return ch;
		}	
	}
}
QuestionNode *insertQuestion(QuestionNode *root, Question q)
{
	if (root == NULL)
	{
		root = new QuestionNode;
		root->key = q.id;
		root->data = q;
		root->left = NULL;
		root->right = NULL;
		root->height = 1;
		return root;
	}
	if (q.id < root->key)
		root->left = insertQuestion(root->left, q);
	else
		if (q.id > root->key)
			root->right = insertQuestion(root->right, q);
		else return root; // equal keys are not allowed in BST
	// update height of this ancestor node
	root->height = max(height(root->left), height(root->right)) + 1;
	int balance = getBalance(root);
	// Left left case
	if (balance > 1 && q.id < root->left->key)
		return rightRotate(root);
	// Right right case
	if (balance < -1 && q.id > root->right->key)
		return leftRotate(root);
// Left right case
//	   z                               z                           x
//    / \                            /   \                        /  \ 
//   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
//  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
//T1   x                          y    T3                    T1  T2 T3  T4
//    / \                        / \
//  T2   T3                    T1   T2
	if (balance > 1 && q.id > root->left->key)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
// Right left case
//   z                            z                            x
//  / \                          / \                          /  \ 
//T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
//    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
//   x   T4                      T2   y                  T1  T2  T3  T4
//  / \                              /  \
//T2   T3                           T3   T4
	if (balance < -1 && q.id < root->right->key)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
void addQuestion(QuestionNode *&root, Subject a)
{
	int x = 102, y = 7, horizontal = 98, vertical = 25;
	string addQuestionMenu[9] = {"THEM CAU HOI THI",
								 "Noi dung: ",
								 "A: ",
								 "B: ",
								 "C: ",
								 "D: ",
								 "Dap an: ",
								 "Them cau hoi",
								 "Tro ve"};
	questionTable(addQuestionMenu);
	string answer[4] = {"A", "B", "C", "D"};
	Question q;
	q.maMh = a.maMh;
	q.dapAn = 'A';
	int picked;
	srand(time(NULL));
	q.id = rand();
	for (int i = 0; i < idStack.n; i++) // kiem tra xem so sinh ra co bi trung
	{
		if (q.id == idStack.node[i])
		{
			q.id = rand();
			i = -1;
		}
	}
	push(idStack, q.id);  // luu id vao Stack de kiem tra
	int curRow = 0;
	setColor(FOREGROUND_LIGHTCYAN);
	drawRectangle(x + 3 + addQuestionMenu[1].length(), y - 1 + 3 * 1, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
	char ch = inputHandling1(q.noiDung, x + 4 + addQuestionMenu[1].length(), y + 3, 80, 210, 1);
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
				if (curRow == 0)
				{
					normal();
					drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
					curRow = 7;
					addButton(addQuestionMenu[curRow + 1], x + 26, y + 22, 46, 1, 0, BACKGROUND_LIGHTCYAN);
				}
				else
				{
					if (curRow > 0 && curRow < 5)
					{
						normal();
						drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
						curRow--;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
						if (curRow == 0)	ch = inputHandling1(q.noiDung, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 210, 1);
						if (curRow == 1)	ch = inputHandling1(q.A, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						if (curRow == 2)	ch = inputHandling1(q.B, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						if (curRow == 3)	ch = inputHandling1(q.C, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						on = false;
					}
					else
					{
						if (curRow == 5)
						{
							for (picked = 0; picked < 4 && q.dapAn != 'A' + picked; picked++);
							for (int i = 0; i < 4; i++)
								addButton(answer[i], x + 13 + 5 + 19 * i, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
							addButton(answer[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
							curRow--;
							setColor(FOREGROUND_LIGHTCYAN);
							drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
							ch = inputHandling1(q.D, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
							on = false;
						}
						else
						{
							if (curRow == 6)
							{
								addButton(addQuestionMenu[curRow + 1], x + 26, y + 20, 46, 1, 0, BACKGROUND_BRIGHTWHITE);
								curRow--;
								ch = chooseAnswer(q.dapAn);
								on = false;
							}
							else
							{
								if (curRow == 7)
								{
									addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow--;
									addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case DOWN:
				if (curRow == 7)
				{
					addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_BRIGHTWHITE);
					curRow = 0;
					setColor(FOREGROUND_LIGHTCYAN);
					drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
					ch = inputHandling1(q.noiDung, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 210, 1);
					on = false;
				}
				else
				{
					if (curRow >= 0 && curRow < 4)
					{
						normal();
						drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
						curRow++;
						setColor(FOREGROUND_LIGHTCYAN);
						drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
						if (curRow == 1)	ch = inputHandling1(q.A, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						if (curRow == 2)	ch = inputHandling1(q.B, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						if (curRow == 3)	ch = inputHandling1(q.C, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						if (curRow == 4)	ch = inputHandling1(q.D, x + 4 + addQuestionMenu[1].length(), y + 3 + 3 * curRow, 80, 140, 1);
						on = false;
					}
					else
					{
						if (curRow == 4)
						{
							normal();
							drawRectangle(x + 3 + addQuestionMenu[1].length(), y + 2 + 3 * curRow, horizontal - 3 - addQuestionMenu[1].length() - 2, 3);
							curRow++;
							ch = chooseAnswer(q.dapAn);
							on = false;
						}
						else
						{
							if (curRow == 5)
							{
								for (picked = 0; picked < 4 && q.dapAn != 'A' + picked; picked++);
								for (int i = 0; i < 4; i++)
									addButton(answer[i], x + 13 + 5 + 19 * i, y + 18, 11, 1, 0, BACKGROUND_BRIGHTWHITE);
								addButton(answer[picked], x + 13 + 5 + 19 * picked, y + 18, 11, 1, 0, BACKGROUND_LIGHTYELLOW);
								curRow++;
								addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_LIGHTCYAN);
							}
							else
							{
								if (curRow == 6)
								{
									addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_BRIGHTWHITE);
									curRow++;
									addButton(addQuestionMenu[curRow + 1], x + 26, y + 20 + 2 * (curRow - 6), 46, 1, 0, BACKGROUND_LIGHTCYAN);
								}
							}
						}
					}
				}
				break;
			case ENTER:
				if (curRow < 5)
				{
					ch = DOWN;
					on = false;
				}
				if (curRow == 6)
				{
					if (q.noiDung == "" || q.A == "" || q.B == "" || q.C == "" || q.D == "")
						notification("Khong duoc bo trong bat ky phan nao!", x, y + vertical, horizontal, 3, FOREGROUND_RED);
					else
					{	
						if (q.A == q.B || q.A == q.C || q.A == q.D || q.B == q.C || q.B == q.D || q.C == q.D)
							notification("Dap an khong duoc trung nhau!", x, y + vertical, horizontal, 3, FOREGROUND_RED);
						else
						{
							notification("Them cau hoi thanh cong!", x, y + vertical, horizontal, 3, FOREGROUND_LIGHTGREEN);
							root = insertQuestion(root, q);
							Sleep(700);
							clearPartOfScreen(x, y - 1, horizontal, vertical + 5);
							addQuestion(root, a);
							return;
						}
					}
				}
				if (curRow == 7)
				{
					clearPartOfScreen(x, y - 1, horizontal, vertical + 5);
					return;
				}
				break;
			case ESC:
				clearPartOfScreen(x, y - 1, horizontal, vertical + 5);
				return;
		}	
	}
}
int getNumberOfNode(QuestionNode *root, int count, Subject a)  // tra ve so nut cua mon hoc
{
	if (root != NULL)
	{
		if (root->data.maMh == a.maMh)
			count++;
		count = getNumberOfNode(root->left, count, a);
		count = getNumberOfNode(root->right, count, a);
	}
	return count;
}
void saveId(QuestionNode *root, Stack &idStack)
{
	if (root != NULL)
	{
		push(idStack, root->key);
		saveId(root->left, idStack);
		saveId(root->right, idStack);
	}
}
void saveId(QuestionNode *root, Stack &subjectIdStack, Subject a)
{
	if (root != NULL)
	{
		if (root->data.maMh == a.maMh)
			push(subjectIdStack, root->key);
		saveId(root->left, subjectIdStack, a);
		saveId(root->right, subjectIdStack, a);
	}
}
QuestionNode *searchQuestion(QuestionNode *root, int id)
{
	QuestionNode *temp = root;
	while (temp != NULL && id != temp->key)
		temp = id < temp->key ? temp->left : temp->right;
	return temp;
}
void saveOptions(string option[], QuestionNode *p) // luu noi dung A, B, C, D vao mang answer[]
{
	option[0] = p->data.A;
	option[1] = p->data.B;
	option[2] = p->data.C;
	option[3] = p->data.D;
}
void printQuestion(QuestionNode *p, int index, int curRow)  // index la chi so cac id cua mot mon hoc duoc luu trong stack tam thoi
{
	int x = 58, y = 2;
	drawRectangle2(x + 48, y + 14, 77, 7, BACKGROUND_GRAY);
	clearPartOfScreen(x + 49, y + 15, 75, 5);
	clearPartOfScreen(x + 48, y + 23, 77, 7);
	string option[4];
	saveOptions(option, p);
	normal();
	breakLine(x + 50, y + 16, "Cau " + to_string(index + 1) + ": " + p->data.noiDung, 74);
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x + 49, y + 23 + 2 * i);	cout << char('A' + i) << ". ";
		breakLine(x + 52, y + 23 + 2 * i, option[i], 73);
	}
	if (curRow < 4)
		addButton1(option[curRow], 'A' + curRow, x + 48, y + 23 + 2 * curRow, 77, option[curRow].length() > 73 ? 2 : 1, 0, BACKGROUND_LIGHTCYAN);
}
void printPreorder(QuestionNode *root, int &i)
{
//	if (root != NULL)
//	{
//		cout << "Cau " << i++ << ": ";
//		printQuestion(root,);
//		printPreorder(root->left, i);
//		printPreorder(root->right, i);
//	}
}
void printQuestionList(QuestionNode *root, SubjectList a)
{
//	string maMh;
//	bool on = true;
//	cout << "Chon mon hoc muon xem danh sach cau hoi: "; cin >> maMh;
//	for (int i = 0; i < a.n; i++)
//	{
//		if (maMh == a.mh[i]->maMh)
//		{
//			if (on)
//			{
//				cout << "			DANH SACH CAU HOI MON " << a.mh[i]->tenMh << endl;
//				on = false;
//			}
//			int j = 1;
//			preOrder(root, j);
//			break;
//		}
//	}
}
void saveQuestionList(QuestionNode *root, Subject a) // luu danh sach cau hoi theo mon hoc
{
	ofstream outFile("DSCH_" + a.tenMh + ".txt");
	outFile << getNumberOfNode(root, 0, a) << endl;
	QuestionNode *stack[500];
	int n = 0;
	QuestionNode *temp = root;
	while (temp != NULL)
	{
		if (temp->data.maMh == a.maMh)
		{
			outFile << temp->data.id << endl;
			outFile << temp->data.noiDung << endl
					<< temp->data.A << endl
					<< temp->data.B << endl
					<< temp->data.C << endl
					<< temp->data.D << endl
					<< temp->data.dapAn << endl;
		}
		if (temp->right != NULL)
			stack[n++] = temp->right;
		if (temp->left != NULL)
			temp = temp->left;
		else
			if (n == 0)		break;
			else	temp = stack[--n];
	}
	outFile.close();
}
void loadQuestionList(QuestionNode *&root, SubjectList a)
{
	for (int i = 0; i < a.n; i++)
	{
		ifstream inFile("DSCH_" + a.mh[i]->tenMh + ".txt");
		if (inFile.fail())	continue;
		int slch;
		inFile >> slch;
		inFile.ignore();
		Question q;
		while (slch--)
		{
			inFile >> q.id;
			q.maMh = a.mh[i]->maMh;
			inFile.ignore();
			getline(inFile, q.noiDung);
			getline(inFile, q.A);
			getline(inFile, q.B);
			getline(inFile, q.C);
			getline(inFile, q.D);
			inFile >> q.dapAn;
			root = insertQuestion(root, q);
		}
		inFile.close();
	}
}
