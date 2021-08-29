#ifndef KEYSPACE2_H
#define KEYSPACE2_H

#include "ks2list.h"

int _hashfunc(unsigned key2, int max);
// Хэш-функция.

int _addInKs2(Table *table, Item *item, unsigned key2);
// Добавляет запись во 2 простарнство.

List_nd2 *_getListByKey2(Table *table, unsigned key2);
// Возвращает список элементов по ключу key2.

Item *_getItemByKey2(Table *table, unsigned key2, int release);
// Возвращает Элемент Item по ключу key2 и релизу.

int _delFromKs2(Table *table, unsigned key2, int release);
// Удаляет запись из 2 пространства ключей.

int _getReleaseByKey1(List_nd2 *list_nd2, char *key1);
// Возвращает релиз по ключу key1 среди элементов списка.


#endif