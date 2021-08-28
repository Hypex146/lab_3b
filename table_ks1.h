#ifndef TABLE_KS1_H
#define TABLE_KS1_H

int table_check_key_ks1(Table *table, char *key);
void table_add_ks1_static(Table *table, Item *item, char *key);
Item *get_item_by_ks1_key(Table *table, char *key1);
void table_del_ks1_without_del_item(Table *table, char *key1);
void table_reorganize_ks1(Table *table);
void table_ks1_debug_print(Table* table);
//Item *find_by_ks1_key_static(Table *table, char *key1);
void find_by_ks1_key(Table *table);

#endif