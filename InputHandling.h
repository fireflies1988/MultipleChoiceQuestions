#pragma once

char inputCode(string &s, int coordX, int coordY, int bound);
char inputStdName(string &s, int coordX, int coordY, int bound);
char inputStandard(string &s, int coordX, int coordY, int overflowIndex, int bound);
char inputHandling(string &s, int coordX, int coordY, int overflowIndex, int bound, int mode); // ESC khong thoat
// mode == 0: che do password, mode =! 0: binh thuong
char inputHandling1(string &s, int coordX, int coordY, int overflowIndex, int bound, int mode);  // ESC thoat
char inputDigitOnly(int &number, int coordX, int coordY, int bound);
