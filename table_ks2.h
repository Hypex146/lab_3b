#ifndef TABLE_KS2_H
#define TABLE_KS2_H

int get_unint(unsigned *a);
int hashfunc(unsigned key2, int max);
void table_add_ks2_static(Table *table, Item *item, unsigned key2);
List_nd2 *get_list_by_ks2_key(Table *table, unsigned key2);
void table_del_ks2_without_del_item(Table *table, KeyType2 key2, int release);
void find_by_ks2_key(Table *table);
void table_ks2_debug_print(Table* table);
int get_release_by_key1(List_nd2 *list_nd2, char *key1);
Item *get_item_by_ks2_key(Table *table, unsigned key2, int release);

#endif