#ifndef READER_H
#define READER_H

#include "table.h"

int getUnint(unsigned *a);
// Считать unsign int

int getInt(int *a);
// Считать int

char *getStr();
// Считать char*

int getConstLenStr(char *str, int len);
// Считать char[len]

int readKey1(char *key1, int len);
// Попросить ввести key1.

int readKey2(KeyType2 *key2);
// Попросить ввести key2.

int readFirstNumber(int *firstNumber);
// Попросить ввести firstNumber.

int readSecondNumber(int *secondNumber);
// Попросить ввести secondNumber.

int readString(char **string);
// Попросить ввести string.

int readRelease(int *release);
// Попросить ввести release.

#endif