#include "table.h"

void table_ks1_print(Table *table){
	printf("Table_ks1:\n");
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy == 1){
			printf("Key: %s | ", table->ks1[i].key);
			printf("%d ", table->ks1[i].info->info->first_number);
			printf("%d ", table->ks1[i].info->info->second_number);
			printf("%s\n", table->ks1[i].info->info->string);
		}
	}
}


int table_check_key_ks1(Table *table, KeyType1 key1){
	for (int i=0; i<table->msize1; i++){
		//printf("Befor strcmp -> %d\n", i);
		if (table->ks1[i].busy == 1 && strcmp(table->ks1[i].key, key1) == 0) return 1;
	}
	return 0;
}


void table_add_ks1_static(Table *table, Item *item, KeyType1 key1){
	if (table->csize1 < table->msize1){
		for (int i=0; i<table->msize1; i++){
			if (table->ks1[i].busy!=1){
				memcpy(table->ks1[i].key, key1, (STRLEN+1)*sizeof(char));
				//table->ks1[i].key = key;
				table->ks1[i].info = item;
				table->ks1[i].busy = 1;
				//printf("Write on %d position\n", i");
				return;
			}
		}
	} else{
		return;
	}
}


Item *get_item_by_ks1_key(Table *table, KeyType1 key1){
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy==1 && strcmp(table->ks1[i].key, key1)==0){
			return table->ks1[i].info;
		}
	}
	return NULL;
}


void table_del_ks1_without_del_item(Table *table, KeyType1 key1){
	for (int i=0; i<table->msize1; i++){
		if (!strcmp(table->ks1[i].key, key1)){
			//free(table->ks1[i].key);
			//printf("Opa!\n");
			table->ks1[i].busy = 0;
			return;
		}
	}
}


void table_reorganize_ks1(Table *table){
	int count = 0;
	int i = 0;
	int j = 0;
	while (count!=table->csize1){
		while (table->ks1[i].busy!=0){
			i++;
			count++;
		}
		if (count==table->csize1) continue;
		j = i;
		while (table->ks1[j].busy!=1) j++;
		table->ks1[i].busy = 1;
		table->ks1[j].busy = 0;
		memcpy(table->ks1[i].key, table->ks1[j].key, (STRLEN+1)*sizeof(char));
		table->ks1[i].info = table->ks1[j].info;
		table->ks1[j].info = NULL;
	}
}


void table_ks1_debug_print(Table* table){
	printf("Table_ks1 (debug mod) (csize1=%d):\n", table->csize1);
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy == 1){
			printf("(index=%d busy=1) ", i);
			printf("Key: %s | ", table->ks1[i].key);
			printf("%d ", table->ks1[i].info->info->first_number);
			printf("%d ", table->ks1[i].info->info->second_number);
			printf("%s\n", table->ks1[i].info->info->string);
		} else{
			printf("(index=%d busy=0)\n", i);
		}
	}
}

/*
Item *find_by_ks1_key_static(Table *table, char *key1){
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy==1 && strcmp(table->ks1[i].key, key1)==0){
			return table->ks1[i].info;
		}
	}
	return NULL;
}
*/


void find_by_ks1_key(Table *table){
	if (table->csize1>0){
		printf("Enter the key in ks1 (string)\n");
		KeyType1 key1 = {0};
		scanf("%*c");
		get_const_len_str(key1);
		Item *item = get_item_by_ks1_key(table, key1);
		if (item){
			printf("Key: %s | ", key1);
			printf("%d, ", item->info->first_number);
			printf("%d, ", item->info->second_number);
			printf("%s\n", item->info->string);
		} else{
			printf("Element not found\n");
		}
	} else{
		printf("KS1 is empty\n");
		return;
	}
}

