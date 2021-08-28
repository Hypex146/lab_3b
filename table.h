#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//
#define MAXSIZE1 5
#define MAXSIZE2 5
#define STRLEN 23
typedef int RelType;
typedef int BusyType1;	// [-1, 0, 1]
typedef char KeyType1[STRLEN+1];
typedef unsigned KeyType2;
typedef int IndexType1;
typedef int IndexType2;
//

typedef struct{
	int first_number;
	int second_number;
	char *string;
} InfoType;


typedef struct _Item{
	InfoType *info;		/* указатель на информацию */
	RelType release;	/* версия элемента */
	struct _Item *next;			/* указатель на следующий элемент с данным составным ключем */
	KeyType1 key1;
	KeyType2 key2;
} Item;


typedef struct{
		BusyType1 busy;	/* признак занятости элемента */
		KeyType1 key;	/* ключ элемента, не может быть 0 */
		KeyType1 par;	/* ключ родительского элемента */
		Item *info;		/* указатель на информацию */
} KeySpace1;


typedef struct _Node2{
		//RelType release;	/* номер версии элемента		*/
		Item *info;		/* указатель на информацию		*/
		struct _Node2 *next; 		/* указатель на следующий элемент	*/
} Node2; // List_element


typedef struct{
	Node2 *head;
} List_nd2; // List одинаковых ключей


typedef struct _KeySpace2{
	KeyType2 key;
	//RelType release;
	List_nd2 *node;		/* указатель на список элементов с одинаковым ключом*/
	struct _KeySpace2 *next;	/* указатель на следующий элемент c другим ключом*/
} KeySpace2; // List_element


typedef struct{
	KeySpace2 *head;
} List_ks2; // List


typedef struct{
		KeySpace1 	*ks1;	
		IndexType1 	msize1;
		IndexType1 	csize1;
		List_ks2 	**ks2;
		IndexType2 	msize2;
		IndexType2 	csize2;		
} Table;


int get_int(int *a);
int get_unint(unsigned *a);
char *get_str();
void get_const_len_str(char *str);

Table *table_init(void);
void table_ks1_print(Table *table);
void table_add(Table *table);
void table_del(Table *table);
void table_ks1_debug_print(Table* table);
void table_reorganize_ks1(Table *table);
void find_by_ks1_key(Table *table);
void find_by_ks2_key(Table *table);
void find_by_double_key(Table *table); //
void table_ks2_debug_print(Table* table);
void table_del_by_ks1(Table *table);
void table_del_by_ks2(Table *table); //
void table_del_all_by_ks2(Table *table); //
void table_print(Table *table); //
void table_write_in_file(Table *table); //
int info_write_in_file(InfoType *info); //
void file_info_clear(); //
Table *table_read_from_file(); //
//void clear_info_file(); //
//Table *table_read_from_file(); //


#endif