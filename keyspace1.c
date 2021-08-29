#include "keyspace1.h"

int _checkKey1(Table *table, char *key1){
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy == 1 && strcmp(table->ks1[i].key, key1) == 0) return 1;
	}
	return 0;
}


int _addInKs1(Table *table, Item *item, char *key1){
	if (table->csize1 < table->msize1){
		for (int i=0; i<table->msize1; i++){
			if (table->ks1[i].busy!=1){
				memcpy(table->ks1[i].key, key1, KEY1LEN*sizeof(char));
				table->ks1[i].info = item;
				table->ks1[i].busy = 1;
				return 0;
			}
		}
	} else{
		return 1;
	}
}


Item *_getItemByKey1(Table *table, char *key1){
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy==1 && strcmp(table->ks1[i].key, key1)==0){
			return table->ks1[i].info;
		}
	}
	return NULL;
}


int _delFromKs1(Table *table, char *key1){
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy && !strcmp(table->ks1[i].key, key1)){ //edit
			table->ks1[i].busy = 0;
			return 0;
		}
	}
	return 1;
}


int _reorganizeKs1(Table *table){
	int count = 0;
	int i = 0;
	int j = 0;
	while (count!=table->csize1){
		while (i<table->msize1 && table->ks1[i].busy!=0){
			i++;
			count++;
		}
		if (count==table->csize1) continue;
		j = i;
		while (table->ks1[j].busy!=1) j++;
		table->ks1[i].busy = 1;
		table->ks1[j].busy = 0;
		memcpy(table->ks1[i].key, table->ks1[j].key, KEY1LEN*sizeof(char));
		table->ks1[i].info = table->ks1[j].info;
		table->ks1[j].info = NULL;
	}
	return 0;
}






