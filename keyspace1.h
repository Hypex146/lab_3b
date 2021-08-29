#ifndef KEYSPACE1_H
#define KEYSPACE1_H

#include  "table.h"

int _checkKey1(Table *table, char *key1);
// Возвращает 1, если запись с таким ключом существует, и 0, если не существует.

int _addInKs1(Table *table, Item *item, char *key1);
// Добавляет запись в 1 простарнство.

Item *_getItemByKey1(Table *table, char *key1);
// Возвращает Элемент Item по ключу key1.

int _delFromKs1(Table *table, char *key1);
// Удаляет запись из 1 пространства ключей.

int _reorganizeKs1(Table *table);
// Реорганизовывает 1 пространство ключей.


#endif