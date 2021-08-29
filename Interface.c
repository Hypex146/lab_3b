#include "interface.h"

void printItem(Item *item){
	printf("\n");
	printf("Item:\n");
	printf("key1 -> %s\n", item->key1);
	printf("key2 -> %u\n", item->key2);
	InfoType *info = _readInfoFromFile(item->offset);
	printf("string -> %s\n", info->string);
	printf("first number -> %d\n", info->first_number);
	printf("second number -> %d\n", info->second_number);
	printf("\n");
	_clearInfo(info);
	return;
}


void printInfo(InfoType *info){
	printf("\n");
	printf("Info:\n");
	printf("string -> %s\n", info->string);
	printf("first number -> %d\n", info->first_number);
	printf("second number -> %d\n", info->second_number);
	printf("\n");
	return;
}


void printKeyList(List_nd2 *list){
    if(list->head->next) {
        Node2 *now = list->head->next;
		printf("Elements:\n");
        while (now){
			Item *item = now->info;
			InfoType *info = _readInfoFromFile(item->offset);
            printf("%d ",info->first_number);
			printf("%d ",info->second_number);
			printf("%s\n",info->string);
			_clearInfo(info);
            now = now->next;
        }
    }
	printf("\n");
    return;
}


void printLog(int type){
	if (type==0){
		printf("\n");
		printf("Success!\n");
		printf("\n");
		return;
	}
	if (type==1){
		printf("\n");
		printf("Element not found!\n");
		printf("\n");
		return;
	}
	if (type==2){
		printf("\n");
		printf("Error!\n");
		printf("\n");
		return;
	}
	return;
}


void findByPairKey(Table *table){
	KeyType1 key1 = {0};
	KeyType2 key2;
	readKey1(key1, KEY1LEN);
	readKey2(&key2);
	Item *item = _findByPairKey(table, key1, key2);
	if (item){
		printItem(item);
		return;
	}
	printLog(1);
	return;
}


void delFromTable(Table *table){
	KeyType1 key1 = {0};
	KeyType2 key2;
	readKey1(key1, KEY1LEN);
	readKey2(&key2);
	if (_delFromTable(table, key1, key2)==0){
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void addInTable(Table *table){
	int firstNumber, secondNumber;
	char *string;
	KeyType1 key1 = {0};
	KeyType2 key2;
	readKey1(key1, KEY1LEN);
	readKey2(&key2);
	readFirstNumber(&firstNumber);
	readSecondNumber(&secondNumber);
	readString(&string);
	InfoType *info = _initInfo(firstNumber, secondNumber, string);
	Item *item = _initItem(0, key1, key2);
	if (_addInTable(table, item)==0){
		int offset = _writeInfoInFile(info, table->memList);
		_clearInfo(info);
		item->offset = offset;
		printLog(0);
		return;
	}
	_clearInfo(info);
	free(item);
	printLog(2);
	return;
}


void delFromTableByKey1(Table *table){
	KeyType1 key1 = {0};
	readKey1(key1, KEY1LEN);
	if (_delFromTableByKey1(table, key1)==0){
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void delFromTableByKey2(Table *table){
	KeyType2 key2;
	int release;
	readKey2(&key2);
	readRelease(&release);
	if (_delFromTableByKey2(table, key2, release)==0){
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void delAllFromTableByKey2(Table *table){
	KeyType2 key2;
	readKey2(&key2);
	if (_delAllFromTableByKey2(table, key2)==0){
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void findByKey1(Table *table){
	KeyType1 key1 = {0};
	readKey1(key1, KEY1LEN);
	Item *item = _getItemByKey1(table, key1);
	if (item){
		printItem(item);
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void findByKey2(Table *table){
	KeyType2 key2;
	readKey2(&key2);
	List_nd2 * list = _getListByKey2(table, key2);
	if (list){
		printKeyList(list);
		printLog(0);
		return;
	}
	printLog(1);
	return;
}


void printTable(Table *table){
	printf("Table:\n");
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy==1){
			printItem(table->ks1[i].info);
		}
	}
	printf("End of table\n");
	return;
}


void table_ks1_debug_print(Table* table){
	printf("Table_ks1 (debug mod) (csize1=%d):\n", table->csize1);
	for (int i=0; i<table->msize1; i++){
		if (table->ks1[i].busy == 1){
			InfoType *info = _readInfoFromFile(table->ks1[i].info->offset);
			printf("(index=%d busy=1) ", i);
			printf("Key: %s | ", table->ks1[i].key);
			printf("%d ", info->first_number);
			printf("%d ", info->second_number);
			printf("%s\n", info->string);
			_clearInfo(info);
		} else{
			printf("(index=%d busy=0)\n", i);
		}
	}
}


void table_ks2_debug_print(Table* table){
	printf("KeySpace2 (csize2 -> %d)\n", table->csize2);
	for (int i=0; i<table->msize2; i++){
		int size = 0;
		if (table->ks2[i]) size = _lenHashList(table->ks2[i]);
		printf("Hash func -> %d (size: %d):\n", i, size);
		if (table->ks2[i]){
			for (int j=0; j<_lenHashList(table->ks2[i]); j++){
				KeySpace2 *ks2;
				_takeFromHashList(table->ks2[i], j, &ks2);
				printf("Key -> %u\n", ks2->key);
				printf("Elements: (size: %d)\n", _lenKeyList(ks2->node));
				printKeyList(ks2->node);
			}
		} else{
			printf("~~~Empty~~~\n");
		}
	}
}


void printMenu(void){
	printf("Select one of the following options\n");
	printf("0) Exit\n");
	printf("1) Add element\n");
	printf("2) Delete element\n");
	printf("3) Delete element by ks1 key\n");
	printf("4) Delete element by ks2 key and release\n");
	printf("5) Delete all elements by ks2 key\n");
	printf("6) Find element by ks1 key\n");
	printf("7) Find element by ks2 key\n");
	printf("8) Find element by pair key\n");
	printf("9) Reorganize ks1\n");
	printf("10) Print Table\n");
	printf("11) Print ks1 debug\n");
	printf("12) Print ks2 debug\n");
}


void UI(void){
	int choice;
	Table *table = _readTableFromFile();
	do{
		printMenu();
		do{
			getInt(&choice);
		} while (choice<0 || choice>12);
		switch (choice){
			case 0:{
				_writeTableInFile(table);
				_clearTable(table);
				break;
			}
			case 1:{
				addInTable(table);
				break;
			}
			case 2:{
				delFromTable(table);
				break;
			}
			case 3:{
				delFromTableByKey1(table);
				break;
			}
			case 4:{
				delFromTableByKey2(table);
				break;
			}
			case 5:{
				delAllFromTableByKey2(table);
				break;
			}
			case 6:{
				findByKey1(table);
				break;
			}
			case 7:{
				findByKey2(table);
				break;
			}
			case 8:{
				findByPairKey(table);
				break;
			}
			case 9:{
				_reorganizeKs1(table);
				break;
			}
			case 10:{
				printTable(table);
				break;
			}
			case 11:{
				table_ks1_debug_print(table);
				break;
			}
			case 12:{
				table_ks2_debug_print(table);
				break;
			}
		}
	} while (choice!=0);
}