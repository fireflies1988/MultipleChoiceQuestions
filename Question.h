#pragma once
#include "Config.h"
const int MAX_STACK_SIZE = 1000;

struct Stack
{
	int n = 0;
	int node[MAX_STACK_SIZE];
};
int push(Stack &st, int a);
int pop(Stack &st, int &a);
int max(int a, int b);
int height(QuestionNode *p);
QuestionNode *rightRotate(QuestionNode *z);
QuestionNode *leftRotate(QuestionNode *z);
int getBalance(QuestionNode *p);
QuestionNode *insertQuestion(QuestionNode *root, Question q);
void addQuestion(QuestionNode *&root, Subject a);
int getNumberOfNode(QuestionNode *root, int count, Subject a);
void saveId(QuestionNode *root, Stack &idStack);
void saveId(QuestionNode *root, Stack &subjectIdStack, Subject a);
QuestionNode *searchQuestion(QuestionNode *root, int id);
void saveOptions(string option[], QuestionNode *p);
void printQuestion(QuestionNode *p, int index, int curRow);
void printPreorder(QuestionNode *root, int &i);
void printQuestionList(QuestionNode *root, SubjectList a);
void saveQuestionList(QuestionNode *root, Subject a);
void loadQuestionList(QuestionNode *&root, SubjectList a);
