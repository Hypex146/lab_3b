#include "ks2list.h"

// Для разных ключей, но одного хэш значения

KeySpace2 *_initHashElement(KeyType2 key){
    KeySpace2 *new_list_element = (KeySpace2*)malloc(1 * sizeof(KeySpace2));
    new_list_element->key = key;
	new_list_element->node = _initKeyList();
    new_list_element->next = NULL;
    return new_list_element;
	
}


List_ks2 *_initHashList(void){
    List_ks2 *new_list = (List_ks2*)malloc(1 * sizeof(List_ks2));
    KeySpace2 *header = _initHashElement(0);
    new_list->head = header;
    return new_list;
}


int _insertInHashList(List_ks2 *list, KeyType2 key, int index){
    int i = 0;
    KeySpace2 *now = list->head;
    while (i < index && now->next){
        i++;
        now = now->next;
    }
    KeySpace2 *new_list_element = _initHashElement(key);
    new_list_element->next = now->next;
    now->next = new_list_element;
    return 0;
}


int _removeFromHashList(List_ks2 *list, int index){
    if(list->head->next){
        int i = 0;
        KeySpace2 *now = list->head;
        while (i < index && now->next->next){
            i++;
            now = now->next;
        }
        KeySpace2 *for_del = now->next;
        now->next = now->next->next;
		_clearKeyList(for_del->node);
        free(for_del);
		return 0;
    } else{
		return -1;
	}
}


int _takeFromHashList(List_ks2 *list, int index, KeySpace2 **ret){
	if (list->head->next){
		int i = 0;
		KeySpace2 *now = list->head;
		while(i <= index && now->next){
			i++;
			now = now->next;
		}
		*ret = now;
		return 0;
	} else{
		return -1;
	}
}


int _getIndexFromHashList(List_ks2 *list, KeyType2 key){
	if (list->head->next){
		int i = 0;
		KeySpace2 *now = list->head->next;
		while(now){
			if (now->key == key){
				return i;
			}
			i++;
			now = now->next;
		}
	} else{
		return -1;
	}
	return -1;
}


int _lenHashList(List_ks2* list){
    int count = 0;
    KeySpace2 *now = list->head;
    while (now->next){
        count++;
        now = now->next;
    }
    return count;
}


int _clearHashList(List_ks2 *list){
    KeySpace2 *now = list->head;
    KeySpace2 *tmp = NULL;
    while (now->next){
        tmp = now->next;
		_clearKeyList(now->node);
        free(now);
        now = tmp;
    }
	_clearKeyList(now->node);
    free(now);
    free(list);
    //printf("Clear\n");
    return 0;
}

// Для одинаковых ключей и одного хэш значения ===========================================

Node2 *_initKeyElement(Item *info){
    Node2 *new_list_element = (Node2*)malloc(1 * sizeof(Node2));
    new_list_element->info = info;
    new_list_element->next = NULL;
    return new_list_element;
}


List_nd2 *_initKeyList(void){
    List_nd2 *new_list = (List_nd2*)malloc(1 * sizeof(List_nd2));
    Node2 *header = _initKeyElement(NULL);
    new_list->head = header;
    return new_list;
}


int _insertInKeyList(List_nd2 *list, Item *info, int index){
    int i = 0;
    Node2 *now = list->head;
    while (i < index && now->next){
        i++;
        now = now->next;
    }
    Node2 *new_list_element = _initKeyElement(info);
    new_list_element->next = now->next;
    now->next = new_list_element;
    return 0;
}


int _removeFromKeyList(List_nd2 *list, int index){
    if(list->head->next){
        int i = 0;
        Node2 *now = list->head;
        while (i < index && now->next->next){
            i++;
            now = now->next;
        }
        Node2 *for_del = now->next;
        now->next = now->next->next;
		
        free(for_del);
		return 0;
    } else{
		return -1;
	}
}


int _takeFromKeyList(List_nd2 *list, int index, Node2 **ret){
	if (list->head->next){
		int i = 0;
		Node2 *now = list->head;
		while(i <= index && now->next){
			i++;
			now = now->next;
		}
		*ret = now;
		return 0;
	} else{
		return -1;
	}
}


int _lenKeyList(List_nd2* list){
    int count = 0;
    Node2 *now = list->head;
    while (now->next){
        count++;
        now = now->next;
    }
    return count;
}


int _clearKeyList(List_nd2 *list){
    Node2 *now = list->head;
    Node2 *tmp = NULL;
    while (now->next){
        tmp = now->next;
        free(now);
        now = tmp;
    }
    free(now);
    free(list);
    //printf("Clear\n");
    return 0;
}


