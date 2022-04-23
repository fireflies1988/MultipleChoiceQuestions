#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

const int THE_MAX_NUMBER_OF_SUBJECTS = 200;
const int THE_MAX_NUMBER_OF_CLASSES = 300;

//----------Subject---------
struct Subject
{
	string maMh, tenMh;
};
struct SubjectList
{
	int n = 0;
	Subject *mh[THE_MAX_NUMBER_OF_SUBJECTS];
};
//---------Score------------
struct Score
{
	string maMh;
	double diem;
};
struct ScoreNode  
{
	Score data;
	ScoreNode *next;
};
//---------Student----------
struct Student
{
	string maSv, ho, ten, phai, password;
	ScoreNode *head = NULL;
};
struct StudentNode
{
	Student data;
	StudentNode *next;
};
//----------Class-----------
struct Class
{
	string maLop, tenLop;
	StudentNode *head = NULL;
};
struct ClassList
{
	int n = 0;
	Class lop[THE_MAX_NUMBER_OF_CLASSES];
};
//----------Question-----------
struct Question
{
	int id;
	string maMh, noiDung, A, B, C, D;
	char dapAn;
};
struct QuestionNode
{
	int key;  // id
	int height;  
	Question data;
	QuestionNode *left, *right;
};
