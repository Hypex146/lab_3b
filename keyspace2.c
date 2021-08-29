#include "keyspace2.h"

int _hashfunc(unsigned key2, int max){
	return key2 % max;
}


int _addInKs2(Table *table, Item *item, unsigned key2){
	if (table->csize2 < table->msize2){
		int hash = _hashfunc(key2, table->msize2);
		if (table->ks2[hash]==NULL){
			table->ks2[hash] = _initHashList();
			_insertInHashList(table->ks2[hash], key2, 0);
			KeySpace2 *element_of_ks2 = NULL;
			_takeFromHashList(table->ks2[hash], 0, &element_of_ks2);
			_insertInKeyList(element_of_ks2->node, item, 0);
			return 0;
		} else{
			if (_getIndexFromHashList(table->ks2[hash], key2) == -1){
				_insertInHashList(table->ks2[hash], key2, _lenHashList(table->ks2[hash]));
				KeySpace2 *element_of_ks2 = NULL;
				_takeFromHashList(table->ks2[hash], _lenHashList(table->ks2[hash]), &element_of_ks2);
				_insertInKeyList(element_of_ks2->node, item, 0);
				return 0;
			} else{
				KeySpace2 *element_of_ks2 = NULL;
				int index = _getIndexFromHashList(table->ks2[hash], key2);
				_takeFromHashList(table->ks2[hash], index, &element_of_ks2);
				_insertInKeyList(element_of_ks2->node, item, _lenKeyList(element_of_ks2->node));
				return 0;
			}
		}
	}
	return 1;
}


List_nd2 *_getListByKey2(Table *table, unsigned key2){
	int hash = _hashfunc(key2, table->msize2);
	if (table->ks2[hash]){
		int index = _getIndexFromHashList(table->ks2[hash], key2);
		if (index!=-1){
			KeySpace2 *ks2 = NULL;
			_takeFromHashList(table->ks2[hash], index, &ks2);
			return ks2->node;
		} else{
			return NULL;
		}
	}
	return NULL;
}


Item *_getItemByKey2(Table *table, unsigned key2, int release){
	Item *item = NULL;
	List_nd2 *list = NULL;
	list = _getListByKey2(table, key2);
	if (!list){
		return NULL;
	}
	Node2 *node2 = NULL;
	_takeFromKeyList(list, release, &node2);
	item = node2->info;
	return item;
}


int _delFromKs2(Table *table, unsigned key2, int release){
	int hash = _hashfunc(key2, table->msize2);
	List_nd2 *list_nd2 = _getListByKey2(table, key2);
	if (list_nd2){
		_removeFromKeyList(list_nd2, release);
		if (_lenKeyList(list_nd2)==0){
			int index = _getIndexFromHashList(table->ks2[hash], key2);
			_removeFromHashList(table->ks2[hash], index);
			if (_lenHashList(table->ks2[hash])==0){
				_clearHashList(table->ks2[hash]);
				table->ks2[hash] = NULL;
			}
			return 0;
		}
	}
	return 1;
}


int _getReleaseByKey1(List_nd2 *list_nd2, char *key1){
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




