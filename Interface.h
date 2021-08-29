#ifndef INTERFACE_H
#define INTERFACE_H

#include "keyspace1.h"
#include "keyspace2.h"
#include "reader.h"

void printItem(Item *item);
// Вывод на экран поля таблицы.

void printInfo(InfoType *info);
// Вывод на жкран информации.

void printKeyList(List_nd2 *list);
// Вывод на экран списка полей таблицы с одним ключом.

void printLog(int type);
// Вывод информации об операции.

void findByPairKey(Table *table);
// Поиск поля по двум ключам.

void delFromTable(Table *table);
// Удаление из таблицы по двум ключам

void addInTable(Table *table);
// Добавление в таблицу поля.

void delFromTableByKey1(Table *table);
// Удаление из таблицы по ключу key1.

void delFromTableByKey2(Table *table);
// Удаление из таблицы по ключу key2 и релизу.

void delAllFromTableByKey2(Table *table);
// Удаление из таблицы всех элементов по ключу key2.

void findByKey1(Table *table);
// Поиск поля по ключу key1.

void findByKey2(Table *table);
// Поиск поля по ключу key2.

void printTable(Table *table);
// Вывод таблицы.

void printMenu(void);
// Вывод меню.

void UI(void);
// Интерфейс.



#endif