#include "keyspace1.h"
#include "keyspace2.h"

Table *_initTable(){
	Table *table = (Table*)malloc(sizeof(Table));
	table->msize1 = MAXSIZE1;
	table->csize1 = 0;
	table->ks1 = (KeySpace1*)malloc(table->msize1 * sizeof(KeySpace1));
	for (int i=0; i<table->msize1; i++){
		table->ks1[i].busy = 0;
	};
	table->msize2 = MAXSIZE2;
	table->csize2 = 0;
	table->ks2 = (List_ks2**)malloc(table->msize2 * sizeof(List_ks2*));
	for (int i=0; i<table->msize2; i++){
		table->ks2[i] = NULL;
	}
	table->memList = _initMemList();
	readFromFileMemList(table->memList);
	return table;
}


InfoType *_initInfo(int first_number, int second_number, char *string){
	InfoType *info = (InfoType*)malloc(sizeof(InfoType));
	info->first_number = first_number;
	info->second_number = second_number;
	info->string = string;
	return info;
}


Item *_initItem(int offset, KeyType1 key1, KeyType2 key2){
	Item *item = (Item*)malloc(sizeof(Item));
	item->next = NULL;
	item->offset = offset;
	memcpy(item->key1, key1, (KEY1LEN+1)*sizeof(char));
	item->key2 = key2;
	return item;
}


int _getInfoSizeFromFile(int offset){
	int size = -1;
	FILE *file = fopen("info.bin", "rb");
	if (!file) {return size;}
	fseek(file, offset, SEEK_SET);
	int first_number, second_number, len;
	fread(&first_number, 1, sizeof(int), file);
	fread(&second_number, 1, sizeof(int), file);
	fread(&len, 1, sizeof(int), file);
	size = 2*sizeof(int) + (len+1)*sizeof(char);
	fclose(file);
	return size;
}


int _clearItem(Item *item, MemList *memList){
	int offset = item->offset;
	int size = _getInfoSizeFromFile(offset);
	if (size==-1) {return -1;}
	MemElement *memElement = _initMemElement(offset, size);
	_addInMemList(memList, memElement, 0);
	free(item);
	return 0;
}


int _clearInfo(InfoType *info){
	free(info->string);
	free(info);
	return 0;
}


Item *_findByPairKey(Table *table, KeyType1 key1, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int release = _getReleaseByKey1(list, key1);
			if (release>=0){
				Node2 *node2 = NULL;
				_takeFromKeyList(list, release, &node2);
				return node2->info;
			}
		}	
	}
	return NULL;
}


int _delFromTable(Table *table, KeyType1 key1, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int release = _getReleaseByKey1(list, key1);
			if (release>=0){
				Node2 *node2 = NULL;
				_takeFromKeyList(list, release, &node2);
				Item *item = node2->info;
				_delFromKs1(table, key1);
				_delFromKs2(table, key2, release);
				_clearItem(item, table->memList);
				table->csize1--;
				table->csize2--;
				return 0;
			}
		}
	}
	return -1;
}


int _addInTable(Table *table, Item *item){
	if (table->csize1<table->msize1 && table->csize2<table->msize2){
		if (!_checkKey1(table, item->key1)){
			_addInKs1(table, item, item->key1);
			table->csize1++;
			_addInKs2(table, item, item->key2);
			table->csize2++;
			return 0;
		}
	}
	return -1;
}


int _delFromTableByKey1(Table *table, KeyType1 key1){
	if (table->csize1>0){
		if (_checkKey1(table, key1)==1){
			Item *item = _getItemByKey1(table, key1);
			_delFromKs1(table, key1);
			KeyType2 key2 = item->key2;
			List_nd2 *list_nd2 = _getListByKey2(table, key2);
			int release = _getReleaseByKey1(list_nd2, key1);
			_delFromKs2(table, key2, release);
			_clearItem(item, table->memList);
			table->csize1--;
			table->csize2--;
			return 0;
		}
	}
	return -1;
}


int _delFromTableByKey2(Table *table, KeyType2 key2, int release){
	if (table->csize1 > 0){
		Item *item = _getItemByKey2(table, key2, release);
		if (item){
			_delFromKs2(table, key2, release);
			_delFromKs1(table, item->key1);
			_clearItem(item, table->memList);
			table->csize1--;
			table->csize2--;
			return 0;
		}
	}
	return -1;
}


int _delAllFromTableByKey2(Table *table, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int len = _lenKeyList(list);
			for (int i=0; i<len; i++){
				Item *item = NULL;
				Node2 *node2 = NULL;
				_takeFromKeyList(list, 0, &node2);
				item = node2->info;
				_delFromKs2(table, key2, 0);
				_delFromKs1(table, item->key1);
				_clearItem(item, table->memList);
				table->csize1--;
				table->csize2--;
			}
			return 0;
		}
	}
	return -1;
}


int _clearTable(Table *table){
	if (table){
		writeInFileMemList(table->memList);
		for (int i=0; i<table->msize1; i++){
			if (table->ks1[i].busy==1){
				free(table->ks1[i].info);
				//_clearItem(table->ks1[i].info);
			}
		}
		free(table->ks1);
		for (int i=0; i<table->msize2; i++){
			if (table->ks2[i]!=NULL){
				_clearHashList(table->ks2[i]);
			}
		}
		free(table->ks2);
		clearMemList(table->memList);
		free(table);
		return 0;
	}
	return -1;
}


int _writeTableInFile(Table *table){
	FILE *file = fopen("table.bin", "w+b");
	fwrite(&table->csize1, 1, sizeof(IndexType1), file);
	fwrite(&table->msize1, 1, sizeof(IndexType1), file);
	fwrite(&table->csize2, 1, sizeof(IndexType2), file);
	fwrite(&table->msize2, 1, sizeof(IndexType2), file);
	for (int i=0; i<table->msize2; i++){
		if (table->ks2[i]==NULL) {continue;}
		for (KeySpace2 *element=table->ks2[i]->head->next; element; element=element->next){
			int count = _lenKeyList(element->node);
			if (count==0) {continue;}
			int release = 0;
			for (Node2 *nd2=element->node->head->next; nd2; nd2=nd2->next){
				fwrite(&nd2->info->key1, 1, sizeof(KeyType1), file);
				fwrite(&nd2->info->key2, 1, sizeof(KeyType2), file);
				fwrite(&release, 1, sizeof(int), file);
				fwrite(&nd2->info->offset, 1, sizeof(int), file);
				release++;
			}
		}
	}
	fclose(file);
	return 0;
}


int _writeInfoInFile(InfoType *info, MemList *memList){
	int offset = 0;
	FILE *file;
	file = fopen("info.bin", "a+b");
	fclose(file);
	file = fopen("info.bin", "r+b");
	offset = _popOffset(memList, (strlen(info->string)+1)*sizeof(char)+2*sizeof(int));
	if (offset>=0){
		fseek(file, offset, SEEK_SET);
		printf("E1\n");
	} else{
		fseek(file, 0, SEEK_END);
		offset = ftell(file);
		printf("E2\n");
	}
	fwrite(&info->first_number, 1, sizeof(int), file);
	fwrite(&info->second_number, 1, sizeof(int), file);
	int len = strlen(info->string);
	fwrite(&len, 1, sizeof(int), file);
	fwrite(info->string, strlen(info->string)+1, sizeof(char), file);
	fclose(file);
	return offset;
}


InfoType *_readInfoFromFile(int offset){
	FILE *file = fopen("info.bin", "rb");
	if (!file) {return NULL;}
	InfoType *info = NULL;
	fseek(file, offset, SEEK_SET);
	int first_number, second_number, len;
	char* string = NULL;
	fread(&first_number, 1, sizeof(int), file);
	fread(&second_number, 1, sizeof(int), file);
	fread(&len, 1, sizeof(int), file);
	string = (char*)malloc((len+1)*sizeof(char));
	fread(string, len+1, sizeof(char), file);
	info = _initInfo(first_number, second_number, string);
	fclose(file);
	return info;
}


Table *_readTableFromFile(){
	Table *table = _initTable();
	FILE *file = fopen("table.bin", "rb");
	if (!file) {return table;}
	int count1, count2;
	fread(&count1, 1, sizeof(IndexType1), file);
	fread(&table->msize1, 1, sizeof(IndexType1), file);
	fread(&count2, 1, sizeof(IndexType2), file);
	fread(&table->msize2, 1, sizeof(IndexType2), file);
	for (int i=0; i<count1; i++){
		KeyType1 key1 = {0};
		KeyType2 key2 = 0;
		int release = 0, offset = 0;
		fread(&key1, 1, sizeof(KeyType1), file);
		fread(&key2, 1, sizeof(KeyType2), file);
		fread(&release, 1, sizeof(int), file);
		fread(&offset, 1, sizeof(int), file);
		Item *item = _initItem(offset, key1, key2);
		_addInKs1(table, item, key1);
		table->csize1++;
		_addInKs2(table, item, key2);
		table->csize2++;
	}
	fclose(file);
	return table;
}




