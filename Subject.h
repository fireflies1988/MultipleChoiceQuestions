#include "Config.h"

void subjectTable(string menu[5]);
bool checkSubjectCode(SubjectList a, Subject b, int mode); // dung cho them mon hoc
void addSubject(SubjectList &a); 
void deleteSubject(SubjectList &a, int index); 
void adjustSubject(SubjectList &a, int index);
void printSubjectList(SubjectList a, int curRow, int index);
void saveSubjectList(SubjectList a);
void loadSubjectList(SubjectList &a);
bool manipulateSubjectList(SubjectList &a, int &curRow, int &index, int mode);
