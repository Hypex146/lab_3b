#include "table.h"
#include "ks2_list.h"


int hashfunc(unsigned key2, int max){
	return key2 % max;
}


void table_add_ks2_static(Table *table, Item *item, unsigned key2){
	if (table->csize2 < table->msize2){
		int hash = hashfunc(key2, table->msize2);
		if (table->ks2[hash]==NULL){
			table->ks2[hash] = list_init_ks2();
			list_insert_ks2(table->ks2[hash], key2, 0);
			KeySpace2 *element_of_ks2 = NULL;
			list_take_ks2(table->ks2[hash], 0, &element_of_ks2);
			list_insert_nd2(element_of_ks2->node, item, 0);
		} else{
			if (list_value_index_ks2(table->ks2[hash], key2) == -1){
				list_insert_ks2(table->ks2[hash], key2, list_len_ks2(table->ks2[hash]));
				KeySpace2 *element_of_ks2 = NULL;
				list_take_ks2(table->ks2[hash], list_len_ks2(table->ks2[hash]), &element_of_ks2);
				list_insert_nd2(element_of_ks2->node, item, 0);
			} else{
				KeySpace2 *element_of_ks2 = NULL;
				int index = list_value_index_ks2(table->ks2[hash], key2);
				list_take_ks2(table->ks2[hash], index, &element_of_ks2);
				list_insert_nd2(element_of_ks2->node, item, list_len_nd2(element_of_ks2->node));
			}
		}
	} else{
		return;
	}
}


List_nd2 *get_list_by_ks2_key(Table *table, unsigned key2){
	int hash = hashfunc(key2, table->msize2);
	if (table->ks2[hash]){
		int index = list_value_index_ks2(table->ks2[hash], key2);
		if (index!=-1){
			KeySpace2 *ks2 = NULL;
			list_take_ks2(table->ks2[hash], index, &ks2);
			return ks2->node;
		} else{
			return NULL;
		}
	} else{
		return NULL;
	}
}


Item *get_item_by_ks2_key(Table *table, unsigned key2, int release){
	Item *item = NULL;
	List_nd2 *list = NULL;
	list = get_list_by_ks2_key(table, key2);
	if (!list){
		//printf("There are no elements with such a key\n");
		return item;
	}
	Node2 *node2 = NULL;
	list_take_nd2(list, release, &node2);
	item = node2->info;
	return item;
}


void table_del_ks2_without_del_item(Table *table, unsigned key2, int release){
	int hash = hashfunc(key2, table->msize2);
	List_nd2 *list_nd2 = get_list_by_ks2_key(table, key2);
	if (list_nd2){
		list_remove_nd2(list_nd2, release);
		if (list_len_nd2(list_nd2)==0){
			int index = list_value_index_ks2(table->ks2[hash], key2);
			list_remove_ks2(table->ks2[hash], index);
			if (list_len_ks2(table->ks2[hash])==0){
				list_clear_ks2(table->ks2[hash]);
				table->ks2[hash] = NULL;
			}
		}
	} else{
		return;
	}
}


void find_by_ks2_key(Table *table){
	printf("Enter the key in ks2 (unsigned)\n");
	KeyType2 key2;
	get_unint(&key2);
	int hash = hashfunc(key2, table->msize2);
	List_nd2 *list_nd2 = get_list_by_ks2_key(table, key2);
	if (list_nd2){
		printf("Key: %u\n", key2);
		list_write_nd2(list_nd2);
	} else{
		printf("Element not found\n");
	}
}


void table_ks2_debug_print(Table* table){
	printf("KeySpace2 (csize2 -> %d)\n", table->csize2);
	for (int i=0; i<table->msize2; i++){
		int size = 0;
		if (table->ks2[i]) size = list_len_ks2(table->ks2[i]);
		printf("Hash func -> %d (size: %d):\n", i, size);
		if (table->ks2[i]){
			for (int j=0; j<list_len_ks2(table->ks2[i]); j++){
				KeySpace2 *ks2;
				list_take_ks2(table->ks2[i], j, &ks2);
				printf("Key -> %u\n", ks2->key);
				printf("Elements: (size: %d)\n", list_len_nd2(ks2->node));
				list_write_nd2(ks2->node);
			}
		} else{
			printf("~~~Empty~~~\n");
		}
	}
}


int get_release_by_key1(List_nd2 *list_nd2, char *key1){
    if(list_nd2->head->next) {
		int i = 0;
        Node2 *now = list_nd2->head->next;
        while (now){
            if (strcmp(key1, now->info->key1)==0){
				return i;
			}
			i++;
            now = now->next;
        }
    }
    return -1;
}


