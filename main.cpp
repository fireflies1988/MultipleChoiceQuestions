#include "Config.h"
#include "Login.h"
#include "Class.h"
#include "Subject.h"
#include "Question.h"
#include "Student.h"
#include "Score.h"

extern ClassList a;
extern SubjectList b;
QuestionNode *root = NULL;
Stack idStack;

int main() 
{
	ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
	loadClassList(a);
	loadStudentList(a);
	loadSubjectList(b);
	loadQuestionList(root, b);
	loadScoreList(a, b);
	saveId(root, idStack); // get current ID indexes of question list
	login();
//	QuestionNode *root = NULL;
//	addQuestion(root, a);
//	printQuestionList(root, a);
//	Stack idStack;
//	saveId(root, idStack);
//	multipleChoiceTest(a, root, idStack);
}
