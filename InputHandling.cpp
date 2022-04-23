#include "Interface.h"

char inputHandling(string &s, int coordX, int coordY, int overflowIndex, int bound, int mode) // mode == 0: che do password, mode =! 0: binh thuong
{
	gotoxy(coordX, coordY);
	if (s.length() > overflowIndex)
	{
		if (mode != 0)
			for (int i = s.length() - overflowIndex; i < s.length(); i++)
				cout << s[i];
		else	cout << string(overflowIndex, '*');
	}
	else
		cout << (mode != 0 ? s : string(s.length(), '*'));
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ESC)	continue;
			if (ch == ENTER)	break;
			if (ch == '\b' && s.length() != 0)
			{
				if (s.length() <= overflowIndex)
				{
					s.resize(s.length() - 1);
					gotoxy(coordX + s.length(), coordY);
					cout << ' ';
					gotoxy(coordX + s.length(), coordY);
				}
				else
				{
					s.resize(s.length() - 1);
					gotoxy(coordX, coordY);
					if (mode != 0)
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					else	cout << string(overflowIndex, '*');
				}
			} 
			if (ch != '\b' && ch != '\t' && s.length() < bound)
			{
				if (s.length() < overflowIndex)
				{
					s += ch;
					cout << (mode != 0 ?  ch : '*');
				}
				else
				{
					s += ch;
					gotoxy(coordX, coordY);
					if (mode != 0)
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					else	cout << string(overflowIndex, '*');
				}
			}
		}	
	}
	return ch;
}
char inputHandling1(string &s, int coordX, int coordY, int overflowIndex, int bound, int mode)  //dung ESC de thoat
{
	gotoxy(coordX, coordY);
	if (s.length() > overflowIndex)
	{
		if (mode != 0)
			for (int i = s.length() - overflowIndex; i < s.length(); i++)
				cout << s[i];
		else	cout << string(overflowIndex, '*');
	}
	else
		cout << (mode != 0 ? s : string(s.length(), '*'));
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ENTER || ch == ESC)	break;
			if (ch == '\b' && s.length() != 0)
			{
				if (s.length() <= overflowIndex)
				{
					s.resize(s.length() - 1);
					gotoxy(coordX + s.length(), coordY);	cout << ' ';
					gotoxy(coordX + s.length(), coordY);
				}
				else
				{
					s.resize(s.length() - 1);
					gotoxy(coordX, coordY);
					if (mode != 0)
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					else	cout << string(overflowIndex, '*');
				}
			} 
			if (ch != '\b' && ch != '\t' && s.length() < bound)
			{
				if (s.length() < overflowIndex)
				{
					s += ch;
					cout << (mode != 0 ?  ch : '*');
				}
				else
				{
					s += ch;
					gotoxy(coordX, coordY);
					if (mode != 0)
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					else	cout << string(overflowIndex, '*');
				}
			}
		}	
	}
	return ch;
}
char inputStdName(string &s, int coordX, int coordY, int bound)
{
	gotoxy(coordX, coordY);
	cout << s;
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ENTER || ch == ESC)	break;
			if (ch == '\b' && s.length() != 0)
			{
				s.resize(s.length() - 1);
				gotoxy(coordX + s.length(), coordY);	cout << ' ';
				gotoxy(coordX + s.length(), coordY);
			}
			if (ch != '\b' && ch != '\t' && s.length() < bound)
			{
				if (ch == ' ' && s.length() != 0 && s[s.length() - 1] != ' ')
				{
					cout << ch;
					s += ch;
				}
				if (ch != ' ')
				{
					if (s.length() == 0 || s[s.length() - 1] == ' ')
						ch = toupper(ch);
					else
						ch = tolower(ch);
					cout << ch;
					s += ch;
				}
			}
		}
	}
	if (s[s.length() - 1] == ' ')	s.resize(s.length() - 1);	
	return ch;
}
char inputStandard(string &s, int coordX, int coordY, int overflowIndex, int bound)
{
	gotoxy(coordX, coordY);
	if (s.length() > overflowIndex)
	{
		for (int i = s.length() - overflowIndex; i < s.length(); i++)
			cout << s[i];
	}
	else
		cout << s;
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ENTER || ch == ESC)	break;
			if (ch == '\b' && s.length() != 0)
			{
				if (s.length() <= overflowIndex)
				{
					s.resize(s.length() - 1);
					gotoxy(coordX + s.length(), coordY);	cout << ' ';
					gotoxy(coordX + s.length(), coordY);
				}
				else
				{
					s.resize(s.length() - 1);
					gotoxy(coordX, coordY);
					for (int i = s.length() - overflowIndex; i < s.length(); i++)
						cout << s[i];
				}
			}
			if (ch != '\b' && ch != '\t' && s.length() < bound)
			{
				if (ch == ' ' && s.length() != 0 && s[s.length() - 1] != ' ')
				{
					if (s.length() < overflowIndex)
					{
						cout << ch;
						s += ch;
					}
					else
					{
						s += ch;
						gotoxy(coordX, coordY);
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					}
				}
				if (ch != ' ')
				{
					if (s.length() < overflowIndex)
					{
						if (s.length() == 0)	ch = toupper(ch);
						cout << ch;
						s += ch;
					}
					else
					{
						if (s.length() == 0) 	ch = toupper(ch);
						s += ch;
						gotoxy(coordX, coordY);
						for (int i = s.length() - overflowIndex; i < s.length(); i++)
							cout << s[i];
					}
				}
			}
		}
	}
	if (s[s.length() - 1] == ' ')	s.resize(s.length() - 1);	
	return ch;
}
char inputCode(string &s, int coordX, int coordY, int bound)
{
	gotoxy(coordX, coordY);
	cout << s;
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ENTER || ch == ESC)	break;
			if (ch == '\b' && s.length() != 0)
			{
				s.resize(s.length() - 1);
				gotoxy(coordX + s.length(), coordY);	cout << ' ';
				gotoxy(coordX + s.length(), coordY);
			}
			if (ch != '\b' && ch != '\t' && s.length() < bound && ch != ' ') 
			{
				ch = toupper(ch);
				cout << ch;
				s += ch;
			}
		}
	}	
	return ch;
}
char inputDigitOnly(int &number, int coordX, int coordY, int bound)
{
	gotoxy(coordX, coordY);
	string numberStr = to_string(number);
	if (numberStr == "0")	numberStr = "";
	cout << numberStr;
	char ch;
	while (1)
	{
		if ((ch = getch()) == -32)
		{
			ch = getch();
			if (ch == UP || ch == DOWN)		break;
		}
		else
		{
			if (ch == ENTER || ch == ESC)	break;
			if (ch == '\b' && numberStr.length() != 0)
			{
				numberStr.resize(numberStr.length() - 1);
				gotoxy(coordX + numberStr.length(), coordY);	cout << ' ';
				gotoxy(coordX + numberStr.length(), coordY);
			}
			if (isdigit(ch) && numberStr.length() < bound) 
			{
				if (ch != '0' || numberStr.length() != 0) 
				{
					cout << ch;
					numberStr += ch;
				}
			}
		}
	}
	if (numberStr != "")	number = stoi(numberStr);
	return ch;
}
