#pragma once
#include "Config.h"

bool checkStudentCode(Student sv, int mode);
void studentTable(string menu[9]);
char chooseSex(bool &isMale);
void addStudent(StudentNode *&p);  
void printStudentList(StudentNode *p, int curRow, int index);
void manipulateStudentList(Class &a, int mode);
StudentNode *getNode(StudentNode *p, int index);
int getNumberOfNode(StudentNode *p);
int getPositionOfNode(StudentNode *p, StudentNode *q);
void saveStudentList(Class a);
void loadStudentList(ClassList &a);
void deleteStudent(StudentNode *&p, int index);
void adjustStudent(StudentNode *&p, int index);
