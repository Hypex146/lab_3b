#include "ks2_list.h"

// Для разных ключей, но одного хэш значения

static KeySpace2 *list_element_init_ks2(KeyType2 key){
    KeySpace2 *new_list_element = (KeySpace2*)malloc(1 * sizeof(KeySpace2));
    new_list_element->key = key;
	new_list_element->node = list_init_nd2();
    new_list_element->next = NULL;
    return new_list_element;
	
} 
// done


List_ks2 *list_init_ks2(void){
    List_ks2 *new_list = (List_ks2*)malloc(1 * sizeof(List_ks2));
    KeySpace2 *header = list_element_init_ks2(0);
    new_list->head = header;
    return new_list;
}
//done


int list_insert_ks2(List_ks2 *list, KeyType2 key, int index){
    int i = 0;
    KeySpace2 *now = list->head;
    while (i < index && now->next){
        i++;
        now = now->next;
    }
    KeySpace2 *new_list_element = list_element_init_ks2(key);
    new_list_element->next = now->next;
    now->next = new_list_element;
    return 0;
}
// done


int list_remove_ks2(List_ks2 *list, int index){
    if(list->head->next){
        int i = 0;
        KeySpace2 *now = list->head;
        while (i < index && now->next->next){
            i++;
            now = now->next;
        }
        KeySpace2 *for_del = now->next;
        now->next = now->next->next;
		
		list_clear_nd2(for_del->node);
        free(for_del);
		return 0;
    } else{
		return -1;
	}
}
// done


int list_take_ks2(List_ks2 *list, int index, KeySpace2 **ret){
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
// done


int list_value_index_ks2(List_ks2 *list, KeyType2 key){
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
// done


int list_len_ks2(List_ks2* list){
    int count = 0;
    KeySpace2 *now = list->head;
    while (now->next){
        count++;
        now = now->next;
    }
    return count;
}
// done


int list_write_ks2(List_ks2 *list){
    printf("List:\n--->\n");
    if(list->head->next) {
        KeySpace2 *now = list->head->next;
        while (now){
            printf("%u ", now->key);
            now = now->next;
        }
    }
    printf("\n--->\n");
    return 0;
}
// done


int list_clear_ks2(List_ks2 *list){
    KeySpace2 *now = list->head;
    KeySpace2 *tmp = NULL;
    while (now->next){
        tmp = now->next;
		
		list_clear_nd2(now->node);
        free(now);
        now = tmp;
    }
	list_clear_nd2(now->node);
    free(now);
    free(list);
    printf("Clear\n");
    return 0;
}
// done


// Для одинаковых ключей и одного хэш значения ===========================================

static Node2 *list_element_init_nd2(Item *info){
    Node2 *new_list_element = (Node2*)malloc(1 * sizeof(Node2));
    new_list_element->info = info;
    new_list_element->next = NULL;
    return new_list_element;
}
// done


List_nd2 *list_init_nd2(void){
    List_nd2 *new_list = (List_nd2*)malloc(1 * sizeof(List_nd2));
    Node2 *header = list_element_init_nd2(NULL);
    new_list->head = header;
    return new_list;
}
// done


int list_insert_nd2(List_nd2 *list, Item *info, int index){
    int i = 0;
    Node2 *now = list->head;
    while (i < index && now->next){
        i++;
        now = now->next;
    }
    Node2 *new_list_element = list_element_init_nd2(info);
    new_list_element->next = now->next;
    now->next = new_list_element;
    return 0;
}
// done


int list_remove_nd2(List_nd2 *list, int index){
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
// done


int list_take_nd2(List_nd2 *list, int index, Node2 **ret){
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
// done


int list_len_nd2(List_nd2* list){
    int count = 0;
    Node2 *now = list->head;
    while (now->next){
        count++;
        now = now->next;
    }
    return count;
}
// done



int list_write_nd2(List_nd2 *list){
    if(list->head->next) {
        Node2 *now = list->head->next;
        while (now){
            printf("%d ",now->info->info->first_number);
			printf("%d ",now->info->info->second_number);
			printf("%s\n",now->info->info->string);
            now = now->next;
        }
    }
	printf("\n");
    return 0;
}
// done


int list_clear_nd2(List_nd2 *list){
    Node2 *now = list->head;
    Node2 *tmp = NULL;
    while (now->next){
        tmp = now->next;
		
        free(now);
        now = tmp;
    }
    free(now);
    free(list);
    printf("Clear\n");
    return 0;
}
// done

