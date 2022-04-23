#include "Question.h"

bool verifyingSubmitBlock(int &hours, int &minutes, int &seconds, bool &warning, clock_t &start);
bool checkRequirement(QuestionNode *root, int soCauHoi, int soPhut, Subject a);
bool resultBlock(char picked[], char answer[], int soCauHoi, int soPhut, Subject a, Stack subjectIdStack, int mode);
bool input(QuestionNode *root, Subject a, int &soCauHoi, int &soPhut);
void convertTime(int time, int &hours, int &minutes, int &seconds);
void updateTimer(int &hours, int &minutes, int &seconds, bool &warning);
void shuffleIdStack(Stack &st);
void reviewTest(QuestionNode *root, Stack subjectIdStack, int soCauHoi, char picked[], char answer[]);
void reviewTest1(QuestionNode *root, StudentNode *p, Class a, Subject b);
void multipleChoiceTest(Subject a, QuestionNode *root, int soCauHoi, int soPhut, int mode);
void saveMultipleChoiceTest(Subject b, StudentNode *p, char picked[], char answer[], int soCauHoi, int soPhut, Stack subjectIdStack);
void loadMultipleChoiceTest(Subject b, StudentNode *p, char picked[], char answer[], int &soCauHoi, int &soPhut, Stack &subjectIdStack);
