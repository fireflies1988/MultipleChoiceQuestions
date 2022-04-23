#include "Config.h"

bool checkClassCode(ClassList a, Class b);
void classTable(string menu[5]);
void addClass(ClassList &a);
void deleteClass(ClassList &a);
void adjustClass(ClassList &a);
void printClassList(ClassList a, int curRow, int index);
bool manipulateClassList(ClassList &a, int &curRow, int &index);
void loadClassList(ClassList &a);
void saveClassList(ClassList a);
