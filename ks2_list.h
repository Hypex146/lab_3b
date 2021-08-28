#ifndef KS2_LIST_H
#define KS2_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "table.h"



// Для разных ключей, но одного хэш значения

List_ks2 *list_init_ks2(void); // Создаёт список
int list_insert_ks2(List_ks2 *list, KeyType2 key, int index); // Вставляет новый элемент по индексу
int list_remove_ks2(List_ks2 *list, int index); // Удаляет элемент по индексу
int list_take_ks2(List_ks2 *list, int index, KeySpace2 **ret); // Берёт значение элемента по индексу и записывает его в *ret
int list_value_index_ks2(List_ks2 *list, KeyType2 key); // Возвращает индекс первого элемента с определённым значением
int list_len_ks2(List_ks2* list); // Возвращает длину списка
int list_write_ks2(List_ks2 *list); // Выводит весь список
int list_clear_ks2(List_ks2 *list); // Удаляет весь список

// Для одинаковых ключей и одного хэш значения

List_nd2 *list_init_nd2(void); // Создаёт список
int list_insert_nd2(List_nd2 *list, Item *info, int index); // Вставляет новый элемент по индексу
int list_remove_nd2(List_nd2 *list, int index); // Удаляет элемент по индексу
int list_take_nd2(List_nd2 *list, int index, Node2 **ret); // Берёт значение элемента по индексу и записывает его в *ret
int list_len_nd2(List_nd2* list); // Возвращает длину списка
int list_write_nd2(List_nd2 *list); // Выводит весь список
int list_clear_nd2(List_nd2 *list); // Удаляет весь список



#endif //KS2_LIST_H
