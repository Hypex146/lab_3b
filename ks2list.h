#ifndef KS2LIST_H
#define KS2LIST_H

#include "table.h"

// Для разных ключей, но одного хэш значения ===========================================

KeySpace2 *_initHashElement(KeyType2 key);
// Создание Хэш-элемента.

List_ks2 *_initHashList(void);
// Создание Хэш-листа.

int _insertInHashList(List_ks2 *list, KeyType2 key, int index);
// Вставка в Хэш-лист.

int _removeFromHashList(List_ks2 *list, int index);
// Удаление из Хэш-листа.

int _takeFromHashList(List_ks2 *list, int index, KeySpace2 **ret);
// Возврат элемента из Хэш-листа.

int _getIndexFromHashList(List_ks2 *list, KeyType2 key);
// Возврат позиции из Хэш-листа.

int _lenHashList(List_ks2* list);
// Возврат длины Хэш-листа.

int _clearHashList(List_ks2 *list);
// Удаление Хэш-листа.

// Для одинаковых ключей и одного хэш значения ===========================================

Node2 *_initKeyElement(Item *info);
// Создание Кей-элемента

List_nd2 *_initKeyList(void);
// Создание Кей-листа.

int _insertInKeyList(List_nd2 *list, Item *info, int index);
// Вставка в Кей-лист

int _removeFromKeyList(List_nd2 *list, int index);
// Удаление из Кей-листа.

int _takeFromKeyList(List_nd2 *list, int index, Node2 **ret);
// Возврат элемента из Кей-листа.

int _lenKeyList(List_nd2* list);
// Возврат длины Кей-листа.

int _clearKeyList(List_nd2 *list);
// Удаление Кей-листа.

#endif