#include "Config.h"

void updateScore(Subject a, ScoreNode *&head, double grade);
int getNumberOfStudentTested(Class a, Subject b);
bool manipulateScoreList(Class a, Subject b, int &curRow, int &index, int mode);
void saveScoreList(Class a, Subject b);
void loadScoreList(ClassList &a, SubjectList b);
void clearScoreList(ScoreNode *&p);
